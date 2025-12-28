#pragma once 

#include <string>
#include <cstdint>
#include <chrono>
#include <iostream>

#include "enums.hpp"

struct Order {
    
    // DO NOT use this to construct ORDER objects,
    // purely for array allocation purposes 
    Order() 
    : price(0),
      qty(0),
      cid(0),
      oid(0),
      recv_time(0),
      side(Side::BUY),
      order_type(OrderType::MARKET),
      ticker(),
      alive(0) 
    {}

    Order(
        Side side,
        OrderType order_type, 
        std::string ticker, 
        uint64_t price, 
        uint64_t quantity,
        uint64_t client_id, 
        uint64_t order_id, 
        uint64_t order_time_placed,
        uint8_t alive
    ) :
        side(side),
        order_type(order_type),
        ticker(ticker),
        price(price),
        qty(quantity),
        cid(client_id),
        oid(order_id),
        recv_time(order_time_placed),
        alive(1)
        /*
        Additional post-MVP 

        original qty (oqty)
        - tracks original qty since the qty field is mutated
        throughout its lifetime 

        alive -> status

        we will add new status fields for orders check docs/order.md



         */
    {} 

    friend std::ostream& operator<<(std::ostream& os, const Order& order) {
        std::cout << "Order Side: "<< static_cast<int>(order.side) << std::endl;
        std::cout << "Order Type: " << static_cast<int>(order.order_type) << std::endl;
        std::cout << "Price: " << order.price << std::endl;
        std::cout << "Quantity: " << order.qty << std::endl;
        std::cout << "Client ID: " << order.cid << std::endl;
        std::cout << "Order ID: " << order.oid << std::endl;
        std::cout << "Received: " << order.recv_time << std::endl;
        std::cout << "Alive? " << static_cast<int>(order.alive) << std::endl;
        return os;
    }

    uint64_t price;
    uint64_t qty; 
    uint64_t cid; // client id 
    uint64_t oid; // order (specific) id
    uint64_t recv_time; // time order was placed
    Side side;
    OrderType order_type;
    std::string ticker; 
    uint8_t alive; // if order is valid or not 
  
};