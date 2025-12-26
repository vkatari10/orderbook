#pragma once
#include <cstdint>

enum struct Side : uint8_t {
    BUY = 0,
    SELL = 1
};

enum struct OrderType : uint8_t {
    MARKET = 0, 
    LIMIT = 1,
    FILL_OR_KILL = 2
};