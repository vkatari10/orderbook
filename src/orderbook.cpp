#include "../include/orderbook.hpp"
#include <algorithm>

void OrderBook::add_order(Order&& order) {
    if (order.side == Side::BUY) { // convert to branchless later (hashmap with ref to bids/asks)
        bids_[order.price].push_back(std::move(order));
    } else {
        asks_[order.price].push_back(std::move(order));
    }
}

void OrderBook::remove_order(Order&& order) {
    if (order.side == Side::BUY) {
        remove_order_helper(bids_, std::move(order));
    } else {
        remove_order_helper(asks_, std::move(order));
    }
}

void OrderBook::remove_order_helper(std::map<uint64_t, std::deque<Order>>& orderbook, Order&& order) {
    erase_if(orderbook[order.price], [&](const Order& o){
        return (o.oid == order.oid); 
    });
}


std::ostream& operator<<(std::ostream& os, const OrderBook& ob) {

    std::cout << "BIDS" << std::endl;
    std::cout << std::endl;

    for (const auto& [k, v] : ob.get_bids()) {
        std::cout << "For Price Level: " << k << std::endl;
        std::cout << std::endl;

        for (const auto& order : v) {
            std::cout << order << std::endl;
        }

        std::cout << std::endl;
    }

    std::cout << "ASKS" << std::endl;
    std::cout << std::endl;

    for (const auto& [k, v] : ob.get_asks()) {
        
        std::cout << "Price Level: " << k << std::endl;
        std::cout << std::endl;

        for (const auto& order : v) {
            std::cout << order << std::endl;
        }

        std::cout << std::endl;

    }

    return os;
}

