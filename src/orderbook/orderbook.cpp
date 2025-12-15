#include "../../include/orderbook/orderbook.hpp"
#include <algorithm>
#include <ostream>

void OrderBook::add_order(Order order) {
    if (order.side == Side::BUY) { // convert to branchless later (hashmap with ref to bids/asks)
        bids_[order.price].push_back(std::move(order));
    } else {
        asks_[order.price].push_back(std::move(order));
    }
}

void OrderBook::remove_order(Order order) {
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

// TODO: replace std::endl with "\n" later, left endl for debug purposes
std::ostream& operator<<(std::ostream& os, const OrderBook& ob) {
    os << "BIDS" << std::endl;
    os << std::endl;

    for (const auto& [k, v] : ob.bids()) {
        os << "For Price Level: " << k << std::endl;
        os << std::endl;
        for (const auto& order : v) {
            os << order << std::endl;
        }
        os << std::endl;
    }

    os << "ASKS" << std::endl;
    os << std::endl;

    for (const auto& [k, v] : ob.asks()) {
        os << "Price Level: " << k << std::endl;
        os << std::endl;

        for (const auto& order : v) {
            os << order << std::endl;
        }

        os << std::endl;

    }

    return os;
}

