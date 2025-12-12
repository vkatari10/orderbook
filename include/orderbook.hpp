#pragma once

#include <map>
#include <deque>
#include <utility>
#include <string>
#include <iostream>
#include <vector>

#include "order.hpp"
#include "trade.hpp"
#include "enums.hpp"


class OrderBook {
public:

    OrderBook(const std::string& ticker) : ticker_(ticker) {};
    
    /**
     * @brief adds an order to the orderbook
     * 
     * @param order order to add
     */
    void add_order(Order&& order) {
        if (order.side == Side::BUY)  // convert to branchless later (hashmap with ref to bids/asks)
            bids_[order.price].push_back(std::move(order));
        else {
            asks_[order.price].push_back(std::move(order));
        }
    }

    void remove_order(Order&& order);




    friend std::ostream& operator<<(std::ostream& os, const OrderBook& ob) {

        std::cout << "BIDS" << std::endl;
        std::cout << std::endl;

        for (const auto& [k, v] : ob.bids_) {
            std::cout << "For Price Level: " << k << std::endl;
            std::cout << std::endl;

            for (const auto& order : v) {
                std::cout << order << std::endl;
            }

            std::cout << std::endl;
        }

        std::cout << "ASKS" << std::endl;
        std::cout << std::endl;

         for (const auto& [k, v] : ob.asks_) {
            std::cout << "Price Level: " << k << std::endl;
            std::cout << std::endl;

            for (const auto& order : v) {
                std::cout << order << std::endl;
            }

            std::cout << std::endl;
        }

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