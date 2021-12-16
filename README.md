# NTBex
Децентрализованная торговая платформа на базе EOS 

[Официальный документ открытой децентрализованной торговой платформы ET] https://github.com/ntbsdev/NTBEx/blob/master/WhitePaper.md)


telegram：https://t.me/ntbmine
##
Описание интерфейса контракта:
1. Создайте пул токенов bancor:
void create(account_name payer, account_name exchange_account, asset eos_supply, account_name  token_contract,  asset token_supply);    
payer:			支付账号,从这个账号转出代币和EOS到bancor池账号    
exchange_account:	bancor池账号,TEST代币和EOS代币都在此账号名下:如:etbexchange1     
eos_supply:		初始化EOS数量:如: 100000.0000 EOS     
token_contract: 	代币属于哪个合约,如:issuemytoken部署创建了TEST代币       
token_supply:		初始化代币数量:如:1000000.0000 TEST代币    

2. Покупайте токены и взимайте плату за 10 000 рынков. Плата за обработку buy_fee_rate распределяется между всеми акционерами пула транзакций
void buytoken( account_name payer, asset eos_quant,account_name token_contract, symbol_type token_symbol, account_name fee_account,int64_t fee_rate);   
payer: Покупка валютного счета
eos_quant:		Покупайте токены с помощью quant EOS
token_contract: Какому контракту принадлежит токен? Например, ТЕСТОВЫЙ токен был создан в ходе развертывания issuemytoken.
token_symbol:		Символ токена, который вы хотите купить: например, ТЕСТ
fee_account:		Номер счета, с которого взимается плата за обработку   
fee_rate:		Ставка платы за обработку: [0,10000), например: 50 эквивалентно 50/100 000; 0 эквивалентно отсутствию платы за обработку 

3. Продавайте токены и взимайте плату за 10 000 рынков.плата за обработку sell_fee_rate, распределяемая между всеми акционерами пула транзакцийvoid selltoken( account_name receiver, account_name token_contract, asset quant ,account_name fee_account,int64_t fee_rate);    
receiver: 	Продавайте монетный аккаунт, получайте EOS
token_contract: К какому контракту относится токен, например, ТЕСТОВЫЙ токен был создан развертыванием issuemytoken
квант: токен кванта, который вы хотите продать
fee_account: номер счета, с которого взимается плата за обработку
fee_rate: Ставка платы за обработку: [0,10000), например: 50 эквивалентно 50/100 000; 0 эквивалентно отсутствию платы за обработку

4. Участвуйте в создании Zhuang, вводите токены EOS и токенов в торговый пул и получайте дивиденды за обработку комиссионных. вводится не менее 1/100 торгового пула, а максимальное количество токенов zhuang составляет рынки.банкир_макс_номер
недействительный обмен::addtoken(имя учетной записи учетной записи, количество активов, имя учетной записи токен_контракт, символ_типа токена_символ)
Учетная запись: Номер платежного счета, перевод токенов и EOS по текущей рыночной цене с этой учетной записи на учетную запись пула bancor
количество: количество добавленных EOS
token_contract: К какому контракту относится токен, например, ТЕСТОВЫЙ токен был создан развертыванием issuemytoken
token_symbol: Новый символ токена
Например: 10 ТЕСТОВ можно купить за 1 ЕВРО на текущем рынке, затем, когда будет добавлено 1000 ЕВРО, 1000 ЕВРО и 10 000 ТЕСТОВ будут переведены со счета в пул bancor.

5. Если дилер выводит токены, он должен вывести всю сумму, и дивиденды за транзакцию будут выплачены пропорционально.
недействительный обмен::вложенный токен(имя учетной записи учетной записи, количество активов, токен_контракта имени учетной записи, символ_типа токена_символ)
Учетная запись: Номер платежного счета, перевод токенов и EOS по текущей рыночной цене на эту учетную запись
количество: Уменьшенное количество EOS
token_contract: К какому контракту относится токен, например, ТЕСТОВЫЙ токен был создан развертыванием issuemytoken
token_symbol: Уменьшенный символ токена
Например: 10 ТЕСТОВ можно купить за 1 EOS на текущем рынке, поэтому, когда 1000 EOS будет уменьшено, 1000 EOS и 10 000 ТЕСТОВ будут переведены из пула bancor на учетную запись.

6. Настройка параметров
недействительный обмен::setparam(имя учетной записи токен_контракт,символ_типа токена_символ, строковое имя параметра, строковый параметр);
token_contract: К какому контракту относится токен, например, ТЕСТОВЫЙ токен был создан развертыванием issuemytoken
token_symbol: Уменьшенный символ токена
имя_параметра: задайте имя параметра, например, exchange_type
параметр: Задать параметры

7. Приостановление обмена
void exchange::pause();

8. Перезапустите обмен
аннулирование обмена::перезапуск();

##
Этапы операции обмена: Номер счета контракта: etbexchanger, используемый для создания обмена; (можно посмотреть на главном веб-сайте)

1.Составить контракт  
eosiocpp -o /eos/contracts/etbexchange/etbexchange.wast  /eos/contracts/etbexchange/etbexchange.cpp /eos/contracts/etbexchange/exchange_state.cpp       
eosiocpp -g /eos/contracts/etbexchange/etbexchange.api  /eos/contracts/etbexchange/etbexchange.cpp

2.Развернуть контракт на обменe
g: cleos  set contract etbexchanger /eos/contracts/etbexchange -p etbexchanger

3.Создайте пул ТЕСТОВЫХ токенов bancor:

Сначала авторизуйте контракт:
cleos set account permission etbexchanger active '{"threshold": 1,"keys": [{"key": "EOS6mBLtJQv5Adv36dDkvWtPP7bqUNArwWXiZCT8711CUBPBTbdnR","weight": 1}],"accounts": [{"permission":{"actor":"etbexchanger","permission":"eosio.code"},"weight":1}]}' owner -p etbexchanger

etbexchanger Перевести 4 EOS и100000000个TEST币到bancor池etbexchange1中:   
cleos  push action etbexchanger create '["etbexchanger","etbexchange1", "4.0000 EOS","issuemytoken","100000000.0000 TEST"]' -p etbexchanger

Отзыв разрешения:   
cleos set account permission etbexchanger active '{"threshold": 1,"keys": [{"key": "EOS6mBLtJQv5Adv36dDkvWtPP7bqUNArwWXiZCT8711CUBPBTbdnR","weight": 1}],"accounts": []}' owner -p etbexchanger

4. Проверьте статус торговли валютой на бирже:cleos get table etbexchanger etbexchanger markets       
{   
  "rows": [{    
      "id": 0,  
      "idxkey": "0x04544553540000003015a4d94ba53176",   
      "supply": "100000000000000 ETBCORE",  
      "base": {     
        "contract": "issuemytoken",             // Протестируйте контрактный аккаунт монеты, вы можете проверить статус выпуска монеты: получить статистику валюты, проверить issuemytoken    
        "balance": "104265457.2018 TEST",       //В настоящее время В пуле фондов есть 104265457.2018 ТЕСТ        "weight": "0.50000000000000000"     
      },        
      "quote": {        
        "contract": "eosio.token",              // Для номера контрактного счета монет EOS вы можете проверить статус выпуска монет: получить статистику валюты eosio.токен EOS
        "balance": "3.8364 EOS",              //В настоящее время пул фондов насчитывает 3,8364 EO

        "weight": "0.50000000000000000"     
      },        
      "exchange_account": "etbexchange1"     //Счет пула фондов: etbexchange1, вышеуказанный ТЕСТ и EOS находятся под этой учетной записью    }],        
  "more": false     
}

cleos get table etbexchanger etbexchanger shareholders
{
  "rows": [{
      "id": 0,
      "idxkey": "0x044554420000000010149ba6a1ae4e56",
      "total_quant": "3.8364 EOS",
      "map_acc_info": [{
          "account": "user11111111",
          "info": {
            "eos_in": "3.8364 EOS",
            "token_in": "104265457.2018 TEST",
            "eos_holding": "3.8364 EOS",
            "token_holding": "104265457.2018 TEST"
          }
        }
      ]
    }],
    "more": false
}

# Этапы транзакции пользователя:

Пользователь 1: пользователь11111111, Пользователь 2: пользователь22222222,

1. Покупайте монеты (авторизуйте eosio перед покупкой монет.Код для контрактной учетной записи etbexchange1, отмените разрешение после покупки монет)

разрешать: cleos  set account permission user11111111 active '{"threshold": 1,"keys": [{"key": "EOS5EwrHc3V4aFjL2ADV9X246yoZgyFdpKj4spKxq3GJBhETndJum","weight": 1}],"accounts": [{"permission":{"actor":"etbexchanger","permission":"eosio.code"},"weight":1}]}' owner -p user11111111

TEST: cleos push action etbexchanger selltoken '["user11111111", "issuemytoken","12439024.3889 TEST", "user11111111", "0" ]' -p user11111111

cleos  set account permission user11111111 active '{"threshold": 1,"keys": [{"key": "EOS5EwrHc3V4aFjL2ADV9X246yoZgyFdpKj4spKxq3GJBhETndJum","weight": 1}],"accounts": []}' owner -p user11111111

3. Для участия в маркет-мейкинге он должен быть больше или равен 1/100 существующего торгового пула  

разрешить: cleos  set account permission user11111111 active '{"threshold": 1,"keys": [{"key": "EOS5EwrHc3V4aFjL2ADV9X246yoZgyFdpKj4spKxq3GJBhETndJum","weight": 1}],"accounts": [{"permission":{"actor":"etbexchanger","permission":"eosio.code"},"weight":1}]}' owner -p user11111111

исполнить: cleos push action etbexchanger addtoken '["user11111111", "1000.0000 EOS","issuemytoken", "4,TEST"]' -p user11111111

Отзыв разрешения: cleos  set account permission user11111111 active '{"threshold": 1,"keys": [{"key": "EOS5EwrHc3V4aFjL2ADV9X246yoZgyFdpKj4spKxq3GJBhETndJum","weight": 1}],"accounts": []}' owner -p user11111111

4. Вывести (должен быть выведен немедленно)

разрешать:cleos  set account permission user11111111 active '{"threshold": 1,"keys": [{"key": "EOS5EwrHc3V4aFjL2ADV9X246yoZgyFdpKj4spKxq3GJBhETndJum","weight": 1}],"accounts": [{"permission":{"actor":"etbexchanger","permission":"eosio.code"},"weight":1}]}' owner -p user11111111
TEST: cleos push action etbexchanger subtoken '["user11111111", "0.0000 EOS","issuemytoken", "4,TEST" ]' -p user11111111

Отзыв разрешения: cleos  set account permission user11111111 active '{"threshold": 1,"keys": [{"key": "EOS5EwrHc3V4aFjL2ADV9X246yoZgyFdpKj4spKxq3GJBhETndJum","weight": 1}],"accounts": []}' owner -p user11111111



