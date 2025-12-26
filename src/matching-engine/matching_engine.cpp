#include "matching-engine/matching_engine.hpp"
#include <algorithm>

#include <iostream>

void MatchingEngine::process(Order& order) {
    if (order.order_type == OrderType::LIMIT) {
        handle_limit_(order);
    } else if (order.order_type == OrderType::MARKET) {
        handle_market_(order);
    }
}

void MatchingEngine::handle_market_(Order& order) {
    if (order.side == Side::BUY) { // walk down the asks if possible for each qty possible

    } else { // Side::SELL

    }
}

void MatchingEngine::handle_limit_(Order& order) {
    if (order.side == Side::BUY) {
        if (order.price >= orderbook_.best_ask()) { // can match
            ledger_.push_back(match_limit_order_(order, orderbook_.best_ask_order(), Side::BUY));
            on_order_qty_zero_(order);
            on_order_qty_zero_(orderbook_.best_ask_order());
        } else {
            orderbook_.add_order(order);
        }
    } else { // Side::SELL
        if (order.price <= orderbook_.best_bid()) {
            ledger_.push_back(match_limit_order_(orderbook_.best_bid_order(), order, Side::SELL));
            on_order_qty_zero_(order);
            on_order_qty_zero_(orderbook_.best_bid_order());
        } else {
            orderbook_.add_order(order);
        }
    }
}

Trade MatchingEngine::match_limit_order_(
    Order& bid_order, 
    Order& ask_order, 
    Side aggressor) {

        uint64_t filled_qty{ std::min(bid_order.qty, ask_order.qty) };
        bid_order.qty -= filled_qty;
        ask_order.qty -= filled_qty;

        uint64_t fill_price{
            (aggressor == Side::BUY) 
            ? std::min(bid_order.price, ask_order.price) 
            : std::max(bid_order.price, ask_order.price)
        };
        
        if (aggressor == Side::BUY) {
            on_part_fill_aggressive_limit_order_(bid_order);
        } else {
            on_part_fill_aggressive_limit_order_(ask_order);
        }

        last_price_ = fill_price;
        return create_trade_(bid_order, ask_order, filled_qty, fill_price);
}

Trade MatchingEngine::create_trade_(
    const Order& bid_order, 
    const Order& ask_order, 
    uint64_t filled_qty, 
    uint64_t trade_price) {

    return Trade(
        bid_order.cid,
        ask_order.cid,
        static_cast<uint64_t>(1), // this is the trade id we will need some static increment variable
        filled_qty,
        trade_price,
        static_cast<int8_t>(1), // trade obj return code; check docs for more info
        bid_order.ticker
    );
}

void MatchingEngine::on_order_qty_zero_(Order& order) {
    if (order.qty > 0) return;
    std::cout << "removing order with id: " << order.oid << "\n";
    orderbook_.remove_order(order.price, order.side);
}

void MatchingEngine::on_part_fill_aggressive_limit_order_(Order& order) {
    if (order.side == Side::BUY) {
        orderbook_.add_order(order);
    } else { // Side::SELL
        orderbook_.add_order(order);
    }
}