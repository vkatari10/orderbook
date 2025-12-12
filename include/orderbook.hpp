#pragma once

#include <map>
#include <deque>
#include <utility>
#include <string>
#include <iostream>
#include <vector>

#include "order.hpp"
#include "trade.hpp"


class OrderBook {
public:

    OrderBook(const std::string& ticker) : ticker_(ticker) {};
    
    /**
     * @brief adds a buy order to the orderbook
     * 
     * @param order the order to add
     */
    void add_buy_order(Order&& order) { // pass by value; caller can choose to pass r/lvalue
        bids_[order.price].push_back(std::move(order));
    }

    /**
     * @brief adds a sell order to the orderbook
     * 
     * @param order the order to add
     */
    void add_sell_order(Order&& order) { // pass by value; caller can choose to pass r/lvalue
        asks_[order.price].push_back(std::move(order));
    }





    friend std::ostream& operator<<(std::ostream& os, const OrderBook& ob) {

        std::cout << "BIDS" << std::endl;

        for (const auto& [k, v] : ob.bids_) {
            std::cout << k << std::endl;

            for (const auto& order : ob.bids_[k]) {

            }


        }

        std::cout << "ASKS" << std::endl;

        return os;
    }

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
};