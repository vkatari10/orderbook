#pragma once

#include <map>
#include <deque>
#include <utility>

#include "order.hpp"


class OrderBook {
public:

    OrderBook() {};
    
    /**
     * @brief adds a order to the orderbook
     * 
     * @param order the order to add
     */
    void add_order(Order&& order) { // pass by value; caller can choose to pass r/lvalue
        orderbook_[order.price].push_back(std::move(order));
    }


    

    



private:
    std::map<uint64_t, std::deque<Order>> orderbook_;
};