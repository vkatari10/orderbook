#include <gtest/gtest.h>
#include "orderbook/orderbook.hpp"
#include <iostream>
#include <cstdint>

TEST(OrderbookTests, OrderbookConstruction) {
    OrderBook ob("XYZ");
    EXPECT_EQ(ob.best_ask(), UINT64_MAX);
    EXPECT_EQ(ob.best_bid(), 0);
}