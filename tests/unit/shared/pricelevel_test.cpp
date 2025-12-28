#include <gtest/gtest.h>
#include "shared/pricelevel.hpp"

TEST(PriceLevelTests, TestConstruction) {
    PriceLevel pl; 

    EXPECT_EQ(pl.empty(), 1);
    EXPECT_EQ(pl.full(), 0);
    EXPECT_EQ(pl.order_count(), 0);
    EXPECT_EQ(pl.total_shares(), 0);
}

TEST(PriceLevelTests, TestPushPop) {
    PriceLevel pl;
    
    Order order = Order(
        Side::BUY,
        OrderType::LIMIT,
        "XYZ",
        1, // price
        2, // qty 
        3, // client id
        4, // order id 
        5, // time placed 
        1 // alive 
    );

    pl.push_back(std::move(order));

    EXPECT_EQ(pl.front().alive, 1);
    EXPECT_EQ(pl.total_shares(), 2);
    EXPECT_EQ(pl.order_count(), 1);
    EXPECT_EQ(pl.empty(), 0);
    EXPECT_EQ(pl.full(), 0);

    pl.pop_front();

    EXPECT_EQ(pl.empty(), 1);
    EXPECT_EQ(pl.full(), 0);
    EXPECT_EQ(pl.order_count(), 0);
    EXPECT_EQ(pl.total_shares(), 0);
    EXPECT_EQ(pl.front().alive, 0);
}