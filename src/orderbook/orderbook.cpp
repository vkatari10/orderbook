#include <algorithm>
#include <ostream>

#include "orderbook/orderbook.hpp"

void OrderBook::add_order(Order order) {
    if (order.side == Side::BUY) { // convert to branchless later (hashmap with ref to bids/asks)
        bids_[order.price].enqueue(std::move(order)); // putting order into orderbook

        // k, v: oid : last item in orderbook at that price in the ring buffer
        orders_[order.oid] = bids_[order.price].back_ptr(); 
    } else {
        asks_[order.price].enqueue(std::move(order));
        orders_[order.oid] = asks_[order.price].back_ptr();
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
        orders_.erase(bids_[price_level].peek().oid);
        bids_[price_level].dequeue();
    } else {    
        orders_.erase(asks_[price_level].peek().oid);
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
        os << v << std::endl;
        os << std::endl;
    }  

    os << "ASKS" << std::endl;
    os << std::endl;

    for (const auto& [k, v] : ob.asks()) {
        if (k == std::numeric_limits<uint64_t>::max()) continue;
        os << "Price Level: " << k << std::endl;
        os << std::endl;
        os << v << std::endl;
    }
    return os;
}

