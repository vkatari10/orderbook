#include <algorithm>
#include <ostream>

#include "orderbook/orderbook.hpp"
#include "shared/dynamic_ringbuffer.hpp"

void OrderBook::add_order(Order order) {
    if (order.side == Side::BUY) { // convert to branchless later (hashmap with ref to bids/asks)
        bids_[order.price].enqueue(std::move(order));
        orders_[order.oid] = bids_[order.price].back();
    } else {
        asks_[order.price].enqueue(std::move(order));
        orders_[order.oid] = asks_[order.price].back();
    }
}

void OrderBook::cancel_order(const Order& order) {
    auto it = orders_.find(order.oid);
    if (it == orders_.end()) return;

    it->second->alive = 0;
    orders_.erase(it);
}

void OrderBook::remove_order(uint64_t price_level, Side side) {    
    if (side == Side::BUY) {
        bids_[price_level].dequeue();
    } else {
        asks_[price_level].dequeue();
    }
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

