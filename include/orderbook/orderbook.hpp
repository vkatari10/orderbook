#pragma once

#include <map>
#include <deque>
#include <string>
#include <vector>

#include "shared/order.hpp"
#include "shared/trade.hpp"
#include "shared/enums.hpp"

using OBDS = std::map<uint64_t, std::deque<Order>>;


class OrderBook {
    
public:

    explicit OrderBook(const std::string& ticker) : ticker_(ticker) {};
    
    /**
     * @brief adds an order to the orderbook
     * 
     * @param order order to add
     */
    void add_order(Order order);

    /**
     * @brief removes an order from the orderbook
     * 
     * @param order order to remove
     */
    void remove_order(Order order);

    /** @brief operator overload for std::cout */
    friend std::ostream& operator<<(std::ostream& os, const OrderBook& ob);

    /** @brief return orderbook ticker */
    const std::string& ticker() const { return ticker_; } 

    /** @brief return orderbook bids */
    const OBDS& bids() const { return bids_; }

    /** @brief return orderbook asks */
    const OBDS& asks() const { return asks_; }

private:
    OBDS bids_;
    OBDS asks_;
    std::vector<Trade> ledger_; // contains transactions for matched orders
    std::string ticker_; // orderbook identifier

    /**
     * @brief removes the order from the given orderbook
     * 
     * @param orderbook the orderbook where the order is located
     * @param order the order to remove
     */
    void remove_order_helper(OBDS& orderbook, Order&& order);

};