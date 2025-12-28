#pragma once 

#include <cstdint>
#include <string>
#include <optional>
#include <deque>

#include "shared/trade.hpp"
#include "shared/order.hpp"
#include "shared/ringbuffer.hpp"
#include "orderbook/orderbook.hpp"

class MatchingEngine {
public:

    explicit MatchingEngine(std::string ticker) : 
        last_price_(0),
        ledger_({}),
        orders_(),
        orderbook_(ticker) {};

    /** 
     * @brief entry point for all orders entering the matching engine
     * 
     * @param order the order to process inside the matching engine
     */
    void process(Order& order);

    /**
     * @brief cancels an order that was already placed
     * 
     * @param order the order to cancel
     */
    void cancel(const Order& order) {orderbook_.cancel_order(order); }

    /** @brief returns the current best asking price */
    uint64_t ask() const { return orderbook_.best_ask(); }

    /** @brief returns the current best bidding price */
    uint64_t bid() const { return orderbook_.best_bid(); }

    /** @brief returns the last market price */
    uint64_t last() const noexcept { return last_price_; }

    /** @brief returns the ledger containing all previous confirmed trades */
    const std::deque<Trade>& ledger() const { return ledger_; } 

    /** @brief returns the orderbook */
    const OrderBook& orderbook() const { return orderbook_; }

    /** @brief returns the inbound ring buffer */
    const RingBuffer<Order, Config::MATCH_ENGINE_INBOUND_RING_BUF_SIZE> orders() const { return orders_; }

    

private:

    uint64_t last_price_; // last market trade price 

    // ledger might be removed and the matching engine may 
    // just use a different data structure to feed the 
    // confirmed trades out, could just be a dedicated 
    // structure to handle outbound comms...
    std::deque<Trade> ledger_; // contains transactions for matched orders
    
    RingBuffer<Order, Config::MATCH_ENGINE_INBOUND_RING_BUF_SIZE> orders_; // incoming orders 
    OrderBook orderbook_; 

    /**
     * @brief creates a trade object given a bid and ask order that 
     * have been matched
     * 
     * @param bid_order the order on the bidding side
     * @param ask_order the order on the asking side
     * @param filled_qty the number of shares that were filled from this trade
     * @param trade_price the price at which the trade occurred
     * @return Trade object based on given information 
     */
    Trade create_trade_(
        const Order& bid_order, 
        const Order& ask_order,
        uint64_t filled_qty, 
        uint64_t trade_price
    );

    /** @brief handle for limit orders */
    void handle_LMT_(Order& order);

    /** @brief handle for market orders */
    void handle_MKT_(Order& order);

    /** @brief handle for FOK orders */
    void handle_FOK_(Order& order);

    /** @brief matching algo for limit buy side orders */
    void match_LMT_buy_(Order& order);

    /** @brief matching algo for limit sell side orders */
    void match_LMT_sell_(Order& order);

    /** @brief matching algo for market buy side orders */
    void match_MKT_buy_(Order& aggressive);

    /** @brief matching algo for market sell side orders */
    void match_MKT_sell_(Order& aggressive);

    /** @brief matching algo for FOK buy side orders */
    void match_FOK_buy_(Order& aggressive);

    /** @brief matching algo for FOK sell side orders */
    void match_FOK_sell_(Order& aggressive);

    /** @brief adds a partially filled aggressive LMT order back to the orderbook */
    void on_partial_fill_aggressive_limit_(Order& order);
}; 