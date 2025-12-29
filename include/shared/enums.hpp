#pragma once
#include <cstdint>

enum struct Side : uint8_t {
    BUY = 0,
    SELL = 1
};

enum struct OrderType : uint8_t {
    MARKET = 0, 
    LIMIT = 1,
};

enum struct TIF : uint8_t { 
    DAY = 0,
    FOK = 1, 
    IOC = 2
};

enum struct Trigger : uint8_t { 
    NONE = 0,
    STOP = 1
};