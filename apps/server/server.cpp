#include <iostream>

#include <orderbook/orderbook.hpp>


int main() {
    
    OrderBook ob("XYZ");

    Order my_order = Order(
        Side::BUY, 
        OrderType::MARKET,
        "XYZ",
        10,
        10,
        10,
        10,
        10,
        1
    );

    ob.add_order(my_order);

    std::cout << ob << std::endl;

    ob.cancel_order(my_order);

    std::cout << ob << std::endl;


    return 0;
}