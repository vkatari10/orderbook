#pragma once

#include <map>
#include <deque>
#include <string>
#include <utility>

#include "shared/order.hpp"
#include "shared/trade.hpp"
#include "shared/enums.hpp"
#include "shared/dynamic_ringbuffer.hpp"

class OrderBook {
public:

    explicit OrderBook(const std::string& ticker) : ticker_(ticker) {
        // add a ask with max possible value
        // add a bid with value of 0 
    };
    
    /**
     * @brief adds an order to the orderbook
     * 
     * @param order order to add
     */
    void add_order(Order order);

    /**
     * @brief cancels an order that was already placed
     * 
     * @param order order to remove
     */
    void cancel_order(const Order& order);

    /**
     * @brief removes an order from the orderbook at a given price level
     * 
     * @param price_level the price level for which the order should be removed 
     */
    void remove_order(uint64_t price_level, Side side);

    /** @brief operator overload for std::cout */
    friend std::ostream& operator<<(std::ostream& os, const OrderBook& ob);

    /** @brief return orderbook ticker */
    const std::string& ticker() const { return ticker_; } 

    /** @brief return orderbook bids */
    const std::map<uint64_t, DynamicRingBuffer<Order>, std::greater<uint64_t>>& bids() const { return bids_; }

    /** @brief return orderbook asks */
    const std::map<uint64_t, DynamicRingBuffer<Order>>& asks() const { return asks_; }

    /** @brief returns the best asking price */
    uint64_t best_ask() const {
        auto it = asks_.begin();
        return it->first;
    }

    /** @brief returns the best bidding price */
    uint64_t best_bid() const {
        auto it = bids_.begin();
        return it->first;
    }

private:
    std::map<uint64_t, DynamicRingBuffer<Order>, std::greater<uint64_t>> bids_; // ig min heap 
    std::map<uint64_t, DynamicRingBuffer<Order>> asks_;
    std::map<uint64_t, Order*> orders_;
    std::string ticker_; // orderbook identifier    
};