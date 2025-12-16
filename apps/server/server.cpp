#include <iostream>

#include <orderbook/orderbook.hpp>

int main() {
    
    OrderBook ob("XYZ");

    std::cout << ob << std::endl;


    return 0;
}