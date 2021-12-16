

#include "ntbexchange.h"
#include <cmath>

namespace  {
    using namespace eosio;
    const int64_t max_fee_rate = 10000;
    const int64_t day = 24 * 3600;
//    const int64_t day = 60;

    /*  
*  payer: номер платежного счета, перевод токенов и EOS с этой учетной записи на учетную запись пула bancor
* учетная запись exchange_account: учетная запись пула bancor, ТЕСТОВЫЕ токены и токены EOS находятся под этим именем учетной записи: например: ntbexchange1
* eos_supply: Инициализировать количество EOS: например: 100000.0000 EOS
* token_contract: К какому контракту относится токен, например: issuemytoken развернул и создал ТЕСТОВЫЙ токен
* token_supply: Инициализировать количество токенов: например: 1000000,0000 ТЕСТОВЫХ токенов                     
    */
    void exchange::create(account_name payer, account_name exchange_account, asset eos_supply, account_name  token_contract,  asset token_supply)
    {
        require_auth( _self );

        eosio_assert(token_supply.amount > 0, "invalid token_supply amount");
        eosio_assert(token_supply.symbol.is_valid(), "invalid token_supply symbol");
        eosio_assert(token_supply.symbol != S(4,EOS), "token_supply symbol cannot be EOS");
        eosio_assert(eos_supply.amount > 0, "invalid eos_supply amount");
        eosio_assert(eos_supply.symbol == S(4,EOS), "eos_supply symbol only support EOS");

        markets _market(_self,_self);

        uint128_t idxkey = (uint128_t(token_contract) << 64) | token_supply.symbol.value;

        auto idx = _market.template get_index<N(idxkey)>();
        auto itr = idx.find(idxkey);

        eosio_assert(itr == idx.end(), "token market already created");

        action(
                permission_level{ payer, N(active) },
                N(eosio.token), N(transfer),
                std::make_tuple(payer, exchange_account, eos_supply, std::string("send EOS to exchange_account"))
        ).send();

        action(
                permission_level{ payer, N(active) },
                token_contract, N(transfer),
                std::make_tuple(payer, exchange_account, token_supply, std::string("send token to exchange_account"))
        ).send();

        auto pk = _market.available_primary_key();
        _market.emplace( _self, [&]( auto& m ) {
            m.id = pk;
            m.idxkey = idxkey;
            m.supply.amount = 100000000000000ll;
            m.supply.symbol = S(0,ETBCORE);
            m.base.contract = token_contract;
            m.base.balance.amount = token_supply.amount;
            m.base.balance.symbol = token_supply.symbol;
            m.quote.contract = N(eosio.token);
            m.quote.balance.amount = eos_supply.amount;
            m.quote.balance.symbol = eos_supply.symbol;

            m.date = time_point_sec(now()/day*day);
            m.total_fee.eos_fee = asset{0, eos_supply.symbol};
            m.total_fee.token_fee = asset{0, token_supply.symbol};
            m.today_fee.eos_fee = asset{0, eos_supply.symbol};
            m.today_fee.token_fee = asset{0, token_supply.symbol};
            m.yesterday_fee.eos_fee = asset{0, eos_supply.symbol};
            m.yesterday_fee.token_fee = asset{0, token_supply.symbol};

            m.exchange_account = exchange_account;
        });

        shareholders _shareholders(_self, _self);
        _shareholders.emplace( _self, [&]( auto& m ) {
            m.id = pk;
            m.idxkey = idxkey;
            m.total_quant = eos_supply;

            m.map_acc_info[payer].eos_in = eos_supply;
            m.map_acc_info[payer].token_in = token_supply;
            m.map_acc_info[payer].eos_holding = eos_supply;
            m.map_acc_info[payer].token_holding = token_supply;

        });
    }


    /*  
*  payer: 	          Покупка валютного счета
* eos_quant: используйте quant EOS для покупки токенов
* token_contract: К какому контракту относится токен, например, ТЕСТОВЫЙ токен был создан развертыванием issuemytoken
* token_symbol: символ токена, который вы хотите купить: например, "4, ТЕСТ", 4 - это десятичная точка выпущенной монеты.
* fee_account: счет, с которого взимается плата за обработку, плательщик==fee_account эквивалентен отсутствию платы за обработку.
* fee_rate: Ставка платы за обработку: [0,10000), например: 50 эквивалентно 50/100 000; 0 эквивалентно отсутствию платы за обработку
* */     * */
    void exchange::buytoken( account_name payer, asset eos_quant,account_name token_contract, symbol_type token_symbol, account_name fee_account,int64_t fee_rate){
        require_auth( payer );

        eosio_assert(eos_quant.amount > 0, "must purchase a positive amount" );
        eosio_assert(eos_quant.symbol == S(4, EOS), "eos_quant symbol must be EOS");
        eosio_assert(token_symbol.is_valid(), "invalid token_symbol");
        eosio_assert(fee_rate >= 0 && fee_rate < max_fee_rate, "invalid fee_rate, 0<= fee_rate < 10000");

        markets _market(_self,_self);

        uint128_t idxkey = (uint128_t(token_contract) << 64) | token_symbol.value;

        print("idxkey=",idxkey,",contract=",token_contract,",symbol=",token_symbol.value);

        auto idx = _market.template get_index<N(idxkey)>();
        auto market = idx.find(idxkey);
        eosio_assert(market!=idx.end(),"token market does not exist");

        auto quant_after_fee = eos_quant;

        if(fee_rate > 0 && payer != fee_account){
            auto fee = calcfee(eos_quant, fee_rate);
            quant_after_fee -= fee;

    //Комиссия за перевод на счет комиссии за обработку 
            action(
                    permission_level{ payer, N(active) },
                    market->quote.contract, N(transfer),
                    std::make_tuple(payer, fee_account, fee, std::string("send EOS fee to fee_account:" + to_string(fee)))
            ).send();
        }

        eosio_assert( quant_after_fee.amount > 0, "quant_after_fee must a positive amount" );

        asset market_fee{0, eos_quant.symbol};
        if(market->buy_fee_rate > 0){///Минус комиссия за обмен
            market_fee = calcfee(eos_quant, market->buy_fee_rate);
        }

        action(
                permission_level{ payer, N(active) },
                market->quote.contract, N(transfer),
                std::make_tuple(payer, market->exchange_account, quant_after_fee, std::string("send EOS to ET included fee:" + to_string(market_fee)))
        ).send();

        quant_after_fee -= market_fee;
        eosio_assert( quant_after_fee.amount > 0, "quant_after_fee2 must a positive amount " );

        print("\nquant_after_fee:");
        quant_after_fee.print();

        asset token_out{0,token_symbol};
        _market.modify( *market, 0, [&]( auto& es ) {
            token_out = es.convert( quant_after_fee,  token_symbol);
            es.quote.balance += market_fee;

            statsfee(es, market_fee, asset{0, token_symbol});
        });
        eosio_assert( token_out.amount > 0, "must reserve a positive amount" );

        action(
                permission_level{ market->exchange_account, N(active) },
                market->base.contract, N(transfer),
                std::make_tuple(market->exchange_account, payer, token_out, std::string("receive token from ET"))
        ).send();
    }




    /* 
* Продавайте токены и взимайте плату за 10 000 рынков.плата за обработку sell_fee_rate, распределяемая между всеми акционерами пула транзакций
* Получатель: продать валютный счет, получить EOS
* token_contract: К какому контракту относится токен, например, ТЕСТОВЫЙ токен был создан развертыванием issuemytoken
* квант: токен кванта, который вы хотите продать
* fee_account: учетная запись, с которой взимается плата за обработку, получатель==fee_account эквивалентен отсутствию платы за обработку.
* fee_rate: Ставка платы за обработку: [0,10000), например: 50 эквивалентно 50/100 000; 0 эквивалентно отсутствию платы за обработку
* */     
    void exchange::selltoken( account_name receiver, account_name token_contract, asset quant ,account_name fee_account,int64_t fee_rate){
        require_auth( receiver );

        eosio_assert(quant.symbol.is_valid(), "invalid token_symbol");
        eosio_assert(quant.symbol != S(4, EOS), "eos_quant symbol must not be EOS");
        eosio_assert(quant.amount > 0, "cannot sell negative byte" );
        eosio_assert(fee_rate >= 0 && fee_rate < max_fee_rate, "invalid fee_rate");

        markets _market(_self,_self);

        uint128_t idxkey = (uint128_t(token_contract) << 64) | quant.symbol.value;

        auto idx = _market.template get_index<N(idxkey)>();
        auto market = idx.find(idxkey);
        eosio_assert(market!=idx.end(),"token market does not exist");

        auto quant_after_fee = quant;

        if(fee_rate > 0 && receiver != fee_account ){
            auto fee = calcfee(quant, fee_rate);
            quant_after_fee -= fee;

            action(
                    permission_level{ receiver, N(active) },
                    market->base.contract, N(transfer),
                    std::make_tuple(receiver, fee_account, fee, std::string("send token fee to fee_account:"+to_string(fee)) )
            ).send();
        }

        eosio::asset market_fee{0, quant.symbol};
        if(market->sell_fee_rate > 0){
            market_fee = calcfee(quant, market->sell_fee_rate);
        }

        action(
                permission_level{ receiver, N(active) },
                market->base.contract, N(transfer),
                std::make_tuple(receiver, market->exchange_account, quant_after_fee, std::string("send EOS to ET included fee:"+to_string(market_fee)) )
        ).send();

        quant_after_fee -= market_fee;
        eosio_assert( quant_after_fee.amount > 0, "quant_after_fee must a positive amount" );

        print("\nquant_after_fee:");
        quant_after_fee.print();

        asset tokens_out{0,market->quote.balance.symbol};
        _market.modify( *market, 0, [&]( auto& es ) {
            tokens_out = es.convert( quant_after_fee, market->quote.balance.symbol);
            es.base.balance += market_fee;

            statsfee(es, asset{0, market->quote.balance.symbol},market_fee);
        });

        eosio_assert( tokens_out.amount > 0, "token amount received from selling EOS is too low" );

        action(//交易所账户转出EOS
                permission_level{ market->exchange_account, N(active) },
                market->quote.contract, N(transfer),
                std::make_tuple(market->exchange_account, receiver, tokens_out, std::string("receive EOS from ET") )
        ).send();

    }

    /*  参与做庄,往交易池注入EOS和token代币,享受手续费分红,最少注入交易池的1/100,最多做庄人数为markets.banker_max_number
     *  account:		    支付账号,从这个账号转出当前市场价格的代币和EOS到bancor池账号中
     *  quant:			    新增的EOS量
     *  token_contract: 	代币属于哪个合约,如TEST代币是issuemytoken部署创建的
     *  token_symbol:		新增的代币符号
     * */
    void exchange::addtoken( account_name account,asset quant, account_name token_contract,symbol_type token_symbol ) {
        require_auth( account );

        eosio_assert(quant.amount > 0, "must purchase a positive amount" );
        eosio_assert(quant.symbol == S(4, EOS), "quant symbol must be EOS");
        eosio_assert(token_symbol.is_valid(), "invalid token_symbol");

        markets _market(_self,_self);
        uint128_t idxkey = (uint128_t(token_contract) << 64) | token_symbol.value;

        auto idx = _market.template get_index<N(idxkey)>();
        auto market = idx.find(idxkey);
        eosio_assert(market!=idx.end(),"token market does not exist");

        eosio_assert(quant >= market->quote.balance/100, "eos_quant must be more than 1/100 of current market->quote.balance");//当前投入必须大于等于交易池的1%

        asset token_out = (market->base.balance * quant.amount) / market->quote.balance.amount;//market->base.balance, 是 asset已经防止溢出
        eosio_assert(token_out.amount > 0 , "token_out must reserve a positive amount");

        eosio_assert(market->support_banker, "not support_banker");

        shareholders _shareholders(_self, _self);
        auto idx_shareholders = _shareholders.template get_index<N(idxkey)>();
        auto shareholder = idx_shareholders.find(idxkey);
        eosio_assert(shareholder!=idx_shareholders.end(),"token market does not exist");
        std::map<account_name, holderinfo> map1 = shareholder->map_acc_info;

        if(map1.find(account) == map1.end()){
            eosio_assert(map1.size() < market->banker_max_number, "addtoken number over limit");//判断是否有参股空席
        }

//        //调试信息
//        market->quote.balance.print();
//        market->base.balance.print();
//        shareholder->total_quant.print();

        double quote=market->quote.balance.amount,base=market->base.balance.amount;
        for(auto itr = map1.begin(); itr != map1.end(); itr++){
//            itr->second.eos_holding.print();//调试信息

            //token的计算一定要放在eos之前,因为eos计算之后,eos_holding会改变
            itr->second.token_holding.amount = base * itr->second.eos_holding.amount / shareholder->total_quant.amount;
            eosio_assert(itr->second.token_holding.amount>0 && itr->second.token_holding.amount<=base, "division overflow");

            //eos持有量按占比重新计算
            itr->second.eos_holding.amount = quote * itr->second.eos_holding.amount / shareholder->total_quant.amount;
            eosio_assert(itr->second.eos_holding.amount>0 && itr->second.eos_holding.amount<=quote, "division overflow 2");
        }

        _shareholders.modify( *shareholder, account, [&]( auto& es ) {//保存信息
            es.total_quant = market->quote.balance + quant;//新增股东
            if(map1.find(account) == map1.end()){
                map1[account].eos_in = quant;
                map1[account].token_in = token_out;
                map1[account].eos_holding = quant;
                map1[account].token_holding = token_out;
            }else{
                map1[account].eos_in += quant;
                map1[account].token_in += token_out;
                map1[account].eos_holding += quant;
                map1[account].token_holding += token_out;
            }
            es.map_acc_info = map1;
        });


        action(
                permission_level{ account, N(active) },
                market->quote.contract, N(transfer),
                std::make_tuple(account, market->exchange_account, quant, std::string("add EOS to ET"))
        ).send();

        action(
                permission_level{ account, N(active) },
                market->base.contract, N(transfer),
                std::make_tuple(account, market->exchange_account, token_out, std::string("add token to ET"))
        ).send();

        _market.modify( *market, 0, [&]( auto& es ) {
            es.quote.balance += quant;
            es.base.balance += token_out;
        });

    }
    void exchange::subtoken( account_name account, asset quant, account_name token_contract,symbol_type token_symbol ) {
        require_auth( account );

        eosio_assert(quant.symbol == S(4, EOS), "quant symbol must be EOS");

        markets _market(_self,_self);
        uint128_t idxkey = (uint128_t(token_contract) << 64) | token_symbol.value;

        auto idx = _market.template get_index<N(idxkey)>();
        auto market = idx.find(idxkey);
        eosio_assert(market != idx.end(), "token market does not exist 1");

        shareholders _shareholders(_self, _self);
        auto idx_shareholders = _shareholders.template get_index<N(idxkey)>();
        auto shareholder = idx_shareholders.find(idxkey);
        eosio_assert(shareholder != idx_shareholders.end(), "token market does not exist 2");

        double quote = market->quote.balance.amount, base = market->base.balance.amount;
        std::map<account_name, holderinfo> map1 = shareholder->map_acc_info;

        eosio_assert(map1.find(account) != map1.end(), "account is not exist");

        if(map1.size() == 1){
            quant = market->quote.balance;
        }else{
            for (auto itr = map1.begin(); itr != map1.end(); itr++) {
                itr->second.token_holding.amount = base * itr->second.eos_holding.amount / shareholder->total_quant.amount;
                eosio_assert(itr->second.token_holding.amount>0 && itr->second.token_holding.amount<=base, "division overflow");

                itr->second.eos_holding.amount = quote * itr->second.eos_holding.amount / shareholder->total_quant.amount;
                eosio_assert(itr->second.eos_holding.amount>0 && itr->second.eos_holding.amount<=quote, "division overflow 2");
            }

        }


        int64_t token_out = 0;
        if (quant >= market->quote.balance) {
            quant = market->quote.balance;
            token_out = market->base.balance.amount;
        } else {
            double base = market->base.balance.amount, quote = market->quote.balance.amount, quant_tmp = quant.amount;

            token_out = (base * quant_tmp) / quote;

            eosio_assert(token_out < market->base.balance.amount, "token_out should less than market->base.balance");
            eosio_assert(token_out > 0, "token_out must reserve a positive amount");

             
            eosio_assert(
                        std::fabs(base / quote - (base - token_out) / (quote - quant_tmp)) / (base / quote) <= 0.0001,
                        "ratio before and after should less than or equal to 1/10000");
        }

        action(
                permission_level{ market->exchange_account, N(active) },
                market->quote.contract, N(transfer),
                std::make_tuple( market->exchange_account, account, quant, std::string("receive EOS from ET"))
        ).send();

        action(
                permission_level{ market->exchange_account, N(active) },
                market->base.contract, N(transfer),
                std::make_tuple(market->exchange_account, account, asset{token_out, token_symbol}, std::string("receive token from ET"))
        ).send();

        if(token_out == market->base.balance.amount){
            _market.erase(*market);
            _shareholders.erase(*shareholder);
        }else{
            _market.modify( *market, 0, [&]( auto& es ) {
                es.quote.balance -= quant;
                es.base.balance.amount -= token_out;
            });

            _shareholders.modify( *shareholder, account, [&]( auto& es ) {
                es.total_quant = market->quote.balance;
                map1.erase(account);
                es.map_acc_info = map1;
            });
        }

    }
    void exchange::setparam(account_name token_contract,symbol_type token_symbol, string paramname, string param){
        require_auth( _self );

        markets _market(_self,_self);
        uint128_t idxkey = (uint128_t(token_contract) << 64) | token_symbol.value;

        auto idx = _market.template get_index<N(idxkey)>();
        auto market = idx.find(idxkey);
        eosio_assert(market != idx.end(), "token market does not exist");

        if(!strcmp(paramname.c_str(),"buy_fee_rate")){
            _market.modify( *market, 0, [&]( auto& es ) {
                es.buy_fee_rate = atol(param.c_str());
                eosio_assert(es.buy_fee_rate >= 0 && es.buy_fee_rate < max_fee_rate, "invalid buy_fee_rate, 0<= buy_fee_rate < 10000");
            });
        }else if(!strcmp(paramname.c_str(),"sell_fee_rate")){
            _market.modify( *market, 0, [&]( auto& es ) {
                es.sell_fee_rate = atol(param.c_str());
                eosio_assert(es.sell_fee_rate >= 0 && es.sell_fee_rate < max_fee_rate, "invalid sell_fee_rate, 0<= sell_fee_rate < 10000");
            });
        }else if(!strcmp(paramname.c_str(),"support_banker")){
            _market.modify( *market, 0, [&]( auto& es ) {
                if(!param.compare("false")){
                    es.support_banker = false;
                }else{
                    es.support_banker = true;
                }
            });
        }else if(!strcmp(paramname.c_str(),"banker_max_number")){
            _market.modify( *market, 0, [&]( auto& es ) {
                es.banker_max_number = atol(param.c_str());
            });
        }else{
            eosio_assert(false, "paramname not exists");
        }
    }

      void exchange::pause(){
    }
      void exchange::restart(){
    }


    asset exchange::calcfee(asset quant, uint64_t fee_rate){
        asset fee = quant * fee_rate / max_fee_rate;
        if(fee.amount < 1){
            fee.amount = 1;
        }

        return fee;
    }
    void exchange::statsfee(exchange_state &market, asset eos_fee, asset token_fee){
        market.total_fee.eos_fee += eos_fee;
        market.total_fee.token_fee += token_fee;

        uint32_t nowtime = now();
        uint32_t time = nowtime - market.date.utc_seconds;
        if(time >= 2*day){
            market.date = time_point_sec(nowtime/day*day);
            market.today_fee.eos_fee = eos_fee;
            market.today_fee.token_fee = token_fee;
            market.yesterday_fee.eos_fee.amount = 0;
            market.yesterday_fee.token_fee.amount = 0;
        }else if(time >= day){
            market.date = time_point_sec(nowtime/day*day);
            market.yesterday_fee = market.today_fee;

            market.today_fee.eos_fee = eos_fee;     
            market.today_fee.token_fee = token_fee;
        }else{
            market.today_fee.eos_fee += eos_fee;    
            market.today_fee.token_fee += token_fee;
        }
    }

    string exchange::to_string(asset quant) {
        string retstr = "";
        int64_t p = (int64_t)quant.symbol.precision();
        int64_t p10 = 1;
        while( p > 0  ) {
            p10 *= 10; --p;
        }
        p = (int64_t)quant.symbol.precision();

        char fraction[p+1];
        fraction[p] = '\0';
        auto change = quant.amount % p10;

        for( int64_t i = p -1; i >= 0; --i ) {
            fraction[i] = (change % 10) + '0';
            change /= 10;
        }

        char s[256]={0};

        sprintf(s, "%llu.", quant.amount / p10 );
        printi( quant.amount / p10 );
        retstr += s;
        retstr += fraction;
        retstr +=" ";

        auto sym = quant.symbol.value;
        sym >>= 8;
        for( int i = 0; i < 7; ++i ) {
            char c = (char)(sym & 0xff);
            if( !c ) break;
            retstr += c;
            sym >>= 8;
        }

        return retstr;

    }

}


EOSIO_ABI( ::exchange, (create)(buytoken)(selltoken)(addtoken)(subtoken)(setparam)(pause)(restart))
