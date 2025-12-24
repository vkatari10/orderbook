#include <gtest/gtest.h>
#include <shared/dynamic_ringbuffer.hpp>

TEST(DynamicRingBufferTest, EmptyTests) {
    DynamicRingBuffer<int> drb; 
    EXPECT_EQ(drb.empty(), 1);
    drb.enqueue(1);
    EXPECT_EQ(drb.empty(), 0);
    drb.dequeue();
    EXPECT_EQ(drb.empty(), 1);
    for (int i{}; i < 100; ++i) {
        drb.enqueue(10);
        drb.dequeue();
    }
    EXPECT_EQ(drb.empty(), 1);
}

TEST(DynamicRingBufferTest, EnqueueDequeueTests) {
    DynamicRingBuffer<int> drb;
    drb.enqueue(5);

    EXPECT_EQ(drb.items(), 1);
    EXPECT_EQ(drb.peek(), 5);
    EXPECT_EQ(*(drb.front()), 5);
}

