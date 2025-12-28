#pragma once

#include <map>
#include <string>
#include <utility>
#include <cstdint>
#include <limits>

#include "shared/order.hpp"
#include "shared/trade.hpp"
#include "shared/enums.hpp"
#include "shared/pricelevel.hpp"
#include "shared/config.hpp"

using std::uint64_t; 

class OrderBook {
public:

    explicit OrderBook(const std::string& ticker) : ticker_(ticker) {
        // add a ask with max possible value just to init the orderbook
        Order max_ask;
        max_ask.price = std::numeric_limits<uint64_t>::max();
        max_ask.side = Side::SELL;
        add_order(max_ask);

        Order min_ask;
        min_ask.price = 0;
        min_ask.side = Side::BUY;
        add_order(min_ask);
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
     * @brief removes the order pointer in the orders_
     * variable
     * 
     * @param id the id of the order, must exist 
     */
    void remove_order_ptr(uint64_t id); 

    /** @brief operator overload for std::cout */
    friend std::ostream& operator<<(std::ostream& os, const OrderBook& ob);

    /** @brief return orderbook ticker */
    std::string& ticker() { return ticker_; }
    const std::string& ticker() const { return ticker_; } 

    /** @brief return orderbook bids */
    std::map<uint64_t, PriceLevel, std::greater<uint64_t>>& bids() { return bids_; }
    const std::map<uint64_t, PriceLevel, std::greater<uint64_t>>& bids() const { return bids_; }

    /** @brief return orderbook asks */
    std::map<uint64_t, PriceLevel>& asks() { return asks_; }
    const std::map<uint64_t, PriceLevel>& asks() const { return asks_; }

    /** @brief return map of order id's to pointers of orders for all current orders */
    std::map<uint64_t, Order*>& orders() { return orders_; } 
    const std::map<uint64_t, Order*>& orders() const { return orders_; }

    /** @brief returns the best asking price */
    uint64_t best_ask() const { return asks_.begin()->first; }

    /** @brief returns the best bidding price */
    uint64_t best_bid() const { return bids_.begin()->first; }

private:
    std::map<uint64_t, PriceLevel, std::greater<uint64_t>> bids_; // min heap 
    std::map<uint64_t, PriceLevel> asks_;
    std::map<uint64_t, Order*> orders_;
    std::string ticker_; // orderbook identifier    
};