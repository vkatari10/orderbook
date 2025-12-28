#pragma once 

#include <cstdint>

namespace Config {

// size of the ring buffer at each price level in the orderbook
inline constexpr uint64_t ORDERBOOK_RING_BUF_SIZE = 1024;

// size of the ring buffer for inbound orders waiting to be processed
inline constexpr uint64_t MATCH_ENGINE_INBOUND_RING_BUF_SIZE = 1024;

// size of the price level object's ring buffer in the orderbook
inline constexpr uint64_t ORDERBOOK_PRICE_LVL_RING_BUF_SIZE = 1024;


}