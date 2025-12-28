#include "matching-engine/matching_engine.hpp"
#include <algorithm>

#include <iostream>

void MatchingEngine::process(Order& order) {
    if (order.order_type == OrderType::LIMIT) {
        handle_LMT_(order);
    } else if (order.order_type == OrderType::MARKET) {
        // handle_market_(order);
    }
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

void MatchingEngine::handle_LMT_(Order& order) {
    if (order.side == Side::BUY) {
        match_LMT_buy_(order);
    } else { // Side::SELL
        match_LMT_sell_(order);
    }
}

void MatchingEngine::match_LMT_buy_(Order& order) {

    auto it{ orderbook_.asks().begin() };
    // it->first = price
    // it->second = PriceLevel&


    while (it != orderbook_.asks().end() && order.qty > 0) { 
        if (it->first > order.price) {  
            // add what ever is left on the order
            // useful for init of orderbook if this is the first order coming in 
            on_partial_fill_aggressive_limit_(order);
            return;
        }

        while(!it->second.empty() && order.qty > 0) {

            Order& match = it->second.front(); // first order at this price 
            PriceLevel& level = it->second;

            if (match.alive == 0) { // if order dead
                level.pop_front();
                continue;
            }

            const uint64_t filled_qty{ std::min(order.qty, match.qty) };
            const uint64_t fill_price{ match.price };

            ledger_.emplace_back(
                create_trade_(order, match, filled_qty, fill_price)
            );

            match.qty -= filled_qty;
            order.qty -= filled_qty;

            match.alive = 0; // set  order to dead since match complete 
            orderbook_.remove_order_ptr(match.oid);
            
            level.qty_count_ -= filled_qty;

            if (match.qty == 0) level.pop_front(); // if this first order is empty
        } 

        ++it; // move to next price
    } 

    // if partial fill occurred
    on_partial_fill_aggressive_limit_(order);
}

void MatchingEngine::match_LMT_sell_(Order& order) {

    auto it{ orderbook_.bids().begin() };

    while (it != orderbook_.bids().end() && order.qty > 0) { 
        if (it->first < order.price) {
            on_partial_fill_aggressive_limit_(order);
            return;
        }

        while(!it->second.empty() && order.qty > 0) {

            Order& match = it->second.front();
            PriceLevel& level = it->second;

            if (match.alive == 0) { // if order dead
                level.pop_front();
                continue;
            }

            uint64_t filled_qty{ std::min(order.qty, match.qty) };

            uint64_t fill_price{ match.price };

            ledger_.emplace_back(
                create_trade_(order, match, filled_qty, fill_price)
            );

            match.qty -= filled_qty;
            order.qty -= filled_qty;

            level.qty_count_ -= filled_qty;

            if (match.qty == 0) level.pop_front();
        } 

        ++it;
    } 

    // if partial fill occurred
    on_partial_fill_aggressive_limit_(order);
}

void MatchingEngine::on_partial_fill_aggressive_limit_(Order& order) {
    if (order.qty == 0) return;
    orderbook_.add_order(order);
}


void MatchingEngine::handle_MKT_(Order& order) {
    if (order.side == Side::BUY) {
        match_MKT_buy_(order);
    } else { // Side::SELL
        match_MKT_sell_(order);
    }
}

void MatchingEngine::match_MKT_buy_(Order& order) {

    auto it{ orderbook_.asks().begin() };

    while(it != orderbook_.asks().end() && order.qty > 0) {

        while (!it->second.empty() && order.qty > 0) {

            PriceLevel& level = it->second;
            Order& match = level.front();

            if (match.alive == 0) {
                level.pop_front();
                continue;
            }

            const uint64_t filled_qty{ std::min(order.qty, match.qty) };
            const uint64_t fill_price{ match.price };
            ledger_.emplace_back(
                create_trade_(order, match, filled_qty, fill_price)
            );

            match.qty -= filled_qty;
            order.qty -= filled_qty;
            
            level.qty_count_ -= filled_qty;

            if (match.qty == 0) level.pop_front();
        }

    } 
}

void MatchingEngine::match_MKT_sell_(Order& order) {

    auto it{ orderbook_.bids().begin() };

    while(it != orderbook_.bids().end() && order.qty > 0) {

        while (!it->second.empty() && order.qty > 0) {

            PriceLevel& level = it->second;
            Order& match = level.front();

            if (match.alive == 0) {
                level.pop_front();
                continue;
            }

            const uint64_t filled_qty{ std::min(order.qty, match.qty) };
            const uint64_t fill_price{ match.price };
            ledger_.emplace_back(
                create_trade_(order, match, filled_qty, fill_price)
            );

            match.qty -= filled_qty;
            order.qty -= filled_qty;
            
            level.qty_count_ -= filled_qty;

            if (match.qty == 0) level.pop_front();
        }
    } 
}