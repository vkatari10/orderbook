#pragma once 

#include <string>
#include <cstdint>
#include <chrono>
#include <iostream>

#include "enums.hpp"

struct Order {

    Order(
        Side side,
        OrderType order_type, 
        std::string ticker, 
        uint64_t price, 
        uint64_t quantity,
        uint64_t client_id, 
        uint64_t order_id, 
        uint64_t order_time_placed
    ) :
        side(side),
        order_type(order_type),
        ticker(ticker),
        price(price),
        qty(quantity),
        cid(client_id),
        oid(order_id),
        recv_time(order_time_placed)
    {} 

    friend std::ostream& operator<<(std::ostream& os, const Order& order) {
        std::cout << "Order Side: "<< static_cast<int>(order.side) << std::endl;
        std::cout << "Order Type: " << static_cast<int>(order.order_type) << std::endl;
        std::cout << "Price: " << order.price << std::endl;
        std::cout << "Quantity: " << order.qty << std::endl;
        std::cout << "Client ID: " << order.cid << std::endl;
        std::cout << "Order ID: " << order.oid << std::endl;
        std::cout << "Received: " << order.recv_time << std::endl;
        return os;
    }

    Side side;
    OrderType order_type;
    std::string ticker; 
    uint64_t price;
    uint64_t qty; 
    uint64_t cid; // client id 
    uint64_t oid; // order (specific) id
    uint64_t recv_time; // time order was placed
};


//     Order my_order(
//         Side::BUY, 
//         OrderType::LIMIT,
//         "AAPL",
//         static_cast<uint64_t>(5), 
//         static_cast<uint64_t>(5), 
//         static_cast<uint64_t>(5), 
//         static_cast<uint64_t>(5), 
//         static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
//     );

