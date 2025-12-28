#include "orderbook/orderbook.hpp"

#include <algorithm>
#include <ostream>

void OrderBook::add_order(Order order) {
    if (order.side == Side::BUY) { // convert to branchless later (hashmap with ref to bids/asks)
        // k, v: oid : last item in orderbook at that price in the ring buffer
        orders_[order.oid] = bids_[order.price].back_ptr(); 
        bids_[order.price].push_back(std::move(order)); // putting order into orderbook
    } else {
        orders_[order.oid] = asks_[order.price].back_ptr();
        asks_[order.price].push_back(std::move(order));
    }
}  

void OrderBook::cancel_order(const Order& order) {
    if (order.status == 0) return; // order already dead or filled 
    auto order_it = orders_.find(order.oid);
    if (order_it == orders_.end()) return; // order DNE

    order_it->second->status = 0; // set to dead 
    orders_.erase(order_it); // erase from lookup map 

    if (order.side == Side::BUY) { // decrease qty at price level
        bids_.at(order.price).reduce_shares(order.qty);
    } else {
        asks_.at(order.price).reduce_shares(order.qty);
    }
}

void OrderBook::remove_order_ptr(uint64_t id) { 
    auto it = orders_.find(id);
    if (it != orders_.end()) orders_.erase(id);
}

uint64_t OrderBook::asks_total_shares() const {
    auto it = asks_.begin();
    uint64_t shares{};
    while(it != asks_.end()) { 
        shares += it->second.total_shares();
    }
    return shares;
}

uint64_t OrderBook::bids_total_shares() const {
    auto it = asks_.begin();
    uint64_t shares{};
    while(it != bids_.end()) { 
        shares += it->second.total_shares();
    }
    return shares;
}


std::ostream& operator<<(std::ostream& os, const OrderBook& ob) {
    os << "BIDS" << "\n";
    os << "\n";

    for (const auto& [k, v] : ob.bids()) {
        if (k == 0) continue;
        os << "For Price Level: " << k << "\n";
        os << "\n";
        os << v << "\n";
        os << "\n";
    }  

    os << "ASKS" << "\n";
    os << "\n";

    for (const auto& [k, v] : ob.asks()) {
        if (k == std::numeric_limits<uint64_t>::max()) continue;
        os << "Price Level: " << k << "\n";
        os << "\n";
        os << v << "\n";
    }
    return os;
}