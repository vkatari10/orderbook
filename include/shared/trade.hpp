#pragma once
#include <cstdint>
#include <string>

#include "enums.hpp"

using std::uint64_t, std::int8_t;

struct Trade {

    // DO NOT use this to construct TRADE objects,
    // purely for array allocation purposes 
    Trade() :
        bcid(0),
        acid(0),
        tid(0),
        qty(0),
        price(0),
        return_code(0),
        ticker() 
    {}

    Trade(
        uint64_t bidder_id,
        uint64_t asker_id,
        uint64_t trade_id, 
        uint64_t quantity,
        uint64_t price,
        int8_t return_code,
        std::string ticker
    ) : 
        bcid(bidder_id),
        acid(asker_id),
        tid(trade_id),
        qty(quantity),
        price(price),
        return_code(0),
        ticker(ticker)
    {}

    uint64_t bcid; // bidder client id
    uint64_t acid; // asker client id
    uint64_t tid; // trade id
    uint64_t qty; 
    uint64_t price;
    int8_t return_code; // internal
    std::string ticker;

};