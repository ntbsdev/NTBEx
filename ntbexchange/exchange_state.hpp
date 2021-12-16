#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <musl/upstream/include/bits/stdint.h>
#include <eosiolib/time.hpp>

namespace etb {
    using namespace eosio;
    using namespace std;
    using eosio::asset;
    using eosio::symbol_type;
    typedef double real_type;

    struct earnings{
        asset eos_fee;
        asset token_fee;
    };
    struct connector {
        account_name contract;
        asset balance;
        double weight = .5;
    };
   /**
    *  Uses Bancor math to create a 50/50 relay between two asset types. The state of the
    *  bancor exchange is entirely contained within this struct. There are no external
    *  side effects associated with using this API.
    */
   struct exchange_state {
       uint64_t id;
       uint128_t idxkey;
       asset supply;

       connector base;                      
       connector quote;                     
       account_name exchange_account;       
       uint64_t buy_fee_rate;              
       uint64_t sell_fee_rate;             

       time_point_sec date;       
       earnings total_fee;        
       earnings today_fee;        
       earnings yesterday_fee;    

       bool support_banker;               
       uint64_t banker_max_number=100;   

       uint64_t primary_key() const { return id; }

       uint128_t by_contract_sym() const { return idxkey; }

       uint64_t  by_contract() const{return base.contract;};

       asset convert_to_exchange(connector &c, asset in);

       asset convert_from_exchange(connector &c, asset in);

       asset convert( asset from, symbol_type to);

   };

   typedef eosio::multi_index<N(markets), exchange_state,
           indexed_by< N(idxkey), const_mem_fun<exchange_state, uint128_t,  &exchange_state::by_contract_sym>>,
           indexed_by< N(thirdkey), const_mem_fun<exchange_state, uint64_t,  &exchange_state::by_contract>>
   > markets;


//    struct exchange_state1 {
//        uint64_t id;
//        uint128_t idxkey;
//        asset    supply;
//
//        connector base;
//        connector quote;
//        account_name  exchange_account;
//        uint64_t buy_fee_rate;   
//        uint64_t sell_fee_rate;  
//        time_point_sec date;     
//        earnings total_fee;      
//        earnings today_fee;      
//        earnings yesterday_fee;  
//        bool support_addtoken;   
//        uint64_t addtoken_max_number=100;       
//
//        uint64_t primary_key()const { return id;}
//    };
//
//    typedef eosio::multi_index<N(markets1), exchange_state1> markets1;

    struct holderinfo{
        asset eos_in;               
        asset token_in;             
        asset eos_holding;          
        asset token_holding;        
    };
    struct shareholder{
        uint64_t id;
        uint128_t idxkey;

        asset total_quant;                                  
        std::map<account_name, holderinfo> map_acc_info;    

        uint64_t primary_key() const { return id; }

        uint128_t by_contract_sym() const { return idxkey; }

        uint64_t  by_contract() const{return uint64_t(idxkey>>64);};

    };
    typedef eosio::multi_index<N(shareholders), shareholder,
            indexed_by< N(idxkey), const_mem_fun<shareholder, uint128_t,  &shareholder::by_contract_sym>>,
            indexed_by< N(thirdkey), const_mem_fun<shareholder, uint64_t,  &shareholder::by_contract>>
    > shareholders;


} /// namespace eosiosystem
