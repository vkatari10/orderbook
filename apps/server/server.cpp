#include <iostream>

#include <matching-engine/matching_engine.hpp>

#define NL "\n" 
using std::cout;

int main() {
    
    MatchingEngine me("XYZ");
   

    Order buyside = Order(
        Side::BUY, 
        OrderType::LIMIT,
        "XYZ",
        10, // price
        10,
        10,
        987654321,
        10,
        1
    );

     Order sellside = Order(
        Side::SELL, 
        OrderType::LIMIT,
        "XYZ",
        5,
        10,
        10,
        987654321,
        10,
        1
    );

    me.on_order(sellside);
    me.on_order(buyside);

    for (const auto i : me.ledger()) {
        cout << i << NL;
    }

    cout << me.ledger().size() << NL;



    return 0;
}