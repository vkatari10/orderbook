#pragma once 

#include <cstdint>
#include <string>
#include <optional>

#include "shared/trade.hpp"
#include "shared/order.hpp"
#include "shared/dynamic_ringbuffer.hpp"
#include "orderbook/orderbook.hpp"

class MatchingEngine {
public:

    explicit MatchingEngine(std::string ticker) : 
        best_ask_(0),
        best_bid_(0),
        last_price_(0),
        ledger_(20),
        orders_(20),
        orderbook_(ticker) {};

    // if an order can be matched it will match and generate a trade object
    // if an order cannot be matched then it goes to the orderbook
    void on_order(Order order);

    /**
     * @brief cancels an order that was already placed
     * 
     * @param order the order to cancel
     */
    void cancel(const Order& order) {orderbook_.cancel_order(order); }

    /** @brief returns the current best asking price */
    uint64_t ask() const noexcept { return best_ask_; }

    /** @brief returns the current best bidding price */
    uint64_t bid() const noexcept { return best_bid_; }

    /** @brief returns the last market price */
    uint64_t last() const noexcept { return last_price_; }

private:

    uint64_t best_ask_;
    uint64_t best_bid_;
    uint64_t last_price_; // last market trade price 

    // ledger might be removed and the matching engine may 
    // just use a different data structure to feed the 
    // confirmed trades out 
    DynamicRingBuffer<Trade> ledger_; // contains transactions for matched orders
    DynamicRingBuffer<Order> orders_; // incoming orders 
    OrderBook orderbook_; 

    /** 
     * @brief handles market orders
     * 
     * @param order the order to handle 
     * @return trade object indicating a successful match or not
     */
    Trade handle_market_(Order order);

    /** 
     * @brief handles limit orders 
     * 
     * @param order the order to handle 
     * @return trade object indicating a successful match or not 
     */
    Trade handle_limit_(Order order);

    /**
     * @brief creates a trade object given a bid and ask order that 
     * have been matched
     * 
     * @param bid_order the order on the bidding side
     * @param ask_order the order on the asking side
     * @param filled_qty the number of shares that were filled from this trade
     * @param trade_price the price at which the trade occurred
     */
    Trade create_trade_(
        Order bid_order, 
        Order ask_order,
        uint64_t filled_qty, 
        uint64_t trade_price
    );

    
    Trade match_order_(
        Order bid_order, 
        Order ask_order, 
        uint64_t price,
        Side aggressor
    );
        
}; 