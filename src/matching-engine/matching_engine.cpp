#include "matching-engine/matching_engine.hpp"
#include <algorithm>

void MatchingEngine::on_order(Order& order) {

    // NOTE: Orderbook already places orders on bid/ask side 
    // we do not need to handle it here just various order types
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
        if (order.price >= orderbook_.best_ask()) { 
            ledger_.push_back(match_limit_order_(order, orderbook_.best_ask_order(), Side::BUY));
        } else {
            orderbook_.add_order(order);
        }
    } else {
        if (order.price <= orderbook_.best_bid()) {
            ledger_.push_back(match_limit_order_(orderbook_.best_bid_order(), order, Side::SELL));
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
        on_order_qty_zero_(bid_order);
        on_order_qty_zero_(ask_order);

        uint64_t fill_price{};

        if (aggressor == Side::BUY) { // bid order was aggressor
            fill_price = std::min(bid_order.price, ask_order.price);
            return create_trade_(bid_order, ask_order, filled_qty, fill_price);
        } else { // asking order was aggressor
            fill_price = std::max(bid_order.price, ask_order.price);
            return create_trade_(bid_order, ask_order, filled_qty, fill_price);
        }

        last_price_ = fill_price;
}

Trade MatchingEngine::create_trade_(
    const Order& bid_order, 
    const Order& ask_order, 
    uint64_t filled_qty, 
    uint64_t trade_price) {

    return Trade(
        bid_order.cid,
        ask_order.cid,
        static_cast<uint64_t>(1), // this is the trade id we will need some static atomic variable we can increment to track trade orders
        filled_qty,
        trade_price,
        1, // trade obj return code; check docs for more info
        bid_order.ticker
    );
}

void MatchingEngine::on_order_qty_zero_(const Order& order) {
    if (order.qty != 0) return;
    orderbook_.remove_order(order.price, order.side);
}