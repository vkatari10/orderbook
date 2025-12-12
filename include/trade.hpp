#pragma once
#include <cstdint>
#include <string>

#include "enums.hpp"

struct Trade {

    uint64_t bcid; // bidder client id
    uint64_t acid; // asker client id
    uint64_t tid; // trade id
    std::string ticker;
    uint64_t qty; 
    uint64_t price;
    OrderType order_type;

};