#include <gtest/gtest.h>
#include "orderbook/orderbook.hpp"
#include <iostream>

TEST(OrderbookTests, OrderbookConstruction) {
    OrderBook ob("XYZ");
    EXPECT_EQ(ob.best_ask(), 0);
    EXPECT_EQ(ob.best_bid(), 0);
}