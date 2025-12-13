#pragma once

#include <map>
#include <deque>
#include <string>
#include <ostream>
#include <vector>

#include "order.hpp"
#include "trade.hpp"
#include "enums.hpp"


class OrderBook {
public:

    OrderBook(const std::string& ticker) : ticker_(ticker) {};
    
    /**
     * @brief adds an order to the orderbook, NOTE: parameter requires a xvalue (use std::move())
     * 
     * @param order order to add
     */
    void add_order(Order&& order);

    /**
     * @brief removes an order from the orderbook, NOTE: parameter requires a xvalue (use std::move())
     * 
     * @param order order to remove
     */
    void remove_order(Order&& order);

    /**
     * @brief operator overload for std::cout
     */
    friend std::ostream& operator<<(std::ostream& os, const OrderBook& ob);

    /** @brief return orderbook ticker */
    std::string get_ticker() const { return ticker_; } 

    /** @brief return orderbook bids */
    const std::map<uint64_t, std::deque<Order>>& get_bids() const { return bids_; }

    /** @brief return orderbook asks */
    const std::map<uint64_t, std::deque<Order>>& get_asks() const { return asks_; }

private:
    std::map<uint64_t, std::deque<Order>> bids_;
    std::map<uint64_t, std::deque<Order>> asks_;
    std::vector<Trade> ledger_; // contains transactions for matched orders
    std::string ticker_; // identifier

    /**
     *  @brief removes the order from the given orderbook
     * 
     * @param orderbook the orderbook where the order is located
     * @param order the order to remove
     */
    void remove_order_helper(std::map<uint64_t, std::deque<Order>>& orderbook, Order&& order);

};