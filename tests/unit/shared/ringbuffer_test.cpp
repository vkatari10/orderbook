#include <gtest/gtest.h>
#include <shared/ringbuffer.hpp>

TEST(RingBufferTests, TestConstruction) {
    RingBuffer<int, 10> rb;
    EXPECT_EQ(rb.item_count(), 0);
    rb.dequeue();
    EXPECT_EQ(rb.item_count(), 0);
    EXPECT_EQ(rb.empty(), 1);
    EXPECT_EQ(rb.full(), 0);
}

TEST(RingBufferTests, TestEnqueueDequeue) {
    RingBuffer<int, 10> rb;
    // add 10 items
    for (int i{}; i < rb.capacity(); ++i) {
        rb.enqueue(10);
    }

    EXPECT_EQ(rb.item_count(), 10); 
    EXPECT_EQ(rb.full(), 1);
    EXPECT_EQ(rb.empty(), 0);

    EXPECT_EQ(rb.peek(), 10);

    rb.enqueue(10); // add 11th item 

    // above call should fail to enqueue
    EXPECT_EQ(rb.item_count(), 10);
}


