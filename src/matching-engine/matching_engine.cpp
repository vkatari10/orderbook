#include "matching-engine/matching_engine.hpp"
#include <algorithm>

// 1. try and match the order if possible and generate trade object to the ledger
//      for now the ledger is just kinda there but not being broadcast
//      will figure out later how to work with it 
// 2. if not possible to match then shove the order into the orderbook and leave it 
void MatchingEngine::on_order(Order order) {

    // NOTE: Orderbook already places orders on bid/ask side 
    // we do not need to handle it here just various order types
    if (order.order_type == OrderType::LIMIT) {

        Trade result = handle_limit_(order);

        if (result.return_code != -1) {
            
        }

    } else if (order.order_type == OrderType::MARKET) {

        Trade result = handle_market_(order);

        if (result.return_code != -1) {

        }

    }

    /**
     * if the order can be matched then the order
     * should be immediatley matched and all 
     * other bid, ask prices should be updated 
     * and the trade object should be generated and 
     * pushed out to the people who need to get it 
     */

     /** 
      * if the order cannot be matched then it should just 
      * be placed onto the orderbook and left there at some price level  
      */

}



Trade MatchingEngine::handle_market_(Order order) {

    if (order.side == Side::BUY) { // walk down the asks if possible for each qty possible

    } else { // Side::SELL

    }

    return Trade(); // remove once impl
}

Trade MatchingEngine::handle_limit_(Order order) {

    if (order.side == Side::BUY) {

        // WHAT IF the map is empty?? then what do we compare? 
        // might need to add like 0 and max val just to be on the 
        // safe side?
        if (order.price >= orderbook_.best_ask()) { 
       
        } else {
            orderbook_.add_order(order);
        }
       
    } else { // Side::SELL

        if (order.price <= orderbook_.best_bid()) {
            // match
        } else {
            orderbook_.add_order(order);
        }
    
    }
    
    return Trade(); // remove once impl

}

Trade MatchingEngine::match_order_(
    Order bid_order, 
    Order ask_order, 
    uint64_t price,
    Side aggressor) {

        uint64_t filled_qty{};

        if (aggressor == Side::BUY) { // bid order was aggressor


            return create_trade_(bid_order, ask_order, 1, price);
        } else { // asking order was aggressor


            // REPLACE 1 with actual filled qty!
            return create_trade_(bid_order, ask_order, 1, price);
        }


}

Trade MatchingEngine::create_trade_(
    Order bid_order, 
    Order ask_order, 
    uint64_t filled_qty, 
    uint64_t trade_price) {

    return Trade(
        bid_order.cid,
        ask_order.cid,
        static_cast<uint64_t>(1), // this is the trade id we will need some static atomic variable we can increment to track trade orders
        filled_qty,
        trade_price,
        1, // return code
        bid_order.ticker
    );
}