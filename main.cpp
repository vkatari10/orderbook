#include "include/orderbook.hpp"

#include <iostream>
#include <utility>

int main() {

    OrderBook ob("XYZ");

    Order my_order(
    Side::BUY, 
    OrderType::LIMIT,
    "AAPL",
    static_cast<uint64_t>(5), 
    static_cast<uint64_t>(5), 
    static_cast<uint64_t>(5), 
    static_cast<uint64_t>(5), 
    static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
    );

    ob.add_order(std::move(my_order));

    std::cout << ob << std::endl;

    ob.remove_order(std::move(my_order));

    std::cout << ob << std::endl;

    

    return 0;
}
