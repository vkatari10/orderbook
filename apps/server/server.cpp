#include <iostream>

#include <matching-engine/matching_engine.hpp>

#define NL "\n" 
using std::cout;

int main() {
    
    MatchingEngine me("XYZ");
   

    Order buyside = Order(
        Side::SELL, 
        OrderType::LIMIT,
        TIF::DAY,
        "XYZ",
        10, // price
        10,
        10,
        987654321,
        10,
        1
    );

     Order sellside = Order(
        Side::BUY, 
        OrderType::MARKET,
        TIF::DAY,
        "XYZ",
        10,
        10,
        10,
        987654321,
        10,
        1
    );


    

    
    me.process(buyside);
    me.process(sellside);

    cout << "ledger size atm: " <<  me.ledger().size() << NL;

    cout << "orderbook: " << NL << me.orderbook() << NL;

}