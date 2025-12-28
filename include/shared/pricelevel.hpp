#pragma once

#include <cstdint>
#include <utility>
#include <ostream>

#include "shared/ringbuffer.hpp"
#include "shared/order.hpp"
#include "shared/config.hpp"

using std::uint64_t, std::uint8_t;

class PriceLevel {
public:

    /**
     * @brief total number of shares at this point.
     * NOTE: this variable is public but should only be 
     * modified by an OrderBook object
     */
    uint64_t qty_count_;

    PriceLevel() : rb_(), qty_count_(0) {}

    /**
     * @brief pushes an order to the back of the buffer
     * 
     * @param order the order to push back 
     */
    void push_back(Order&& order) { 
        qty_count_ += order.qty;
        rb_.enqueue(std::move(order)); 
    }

    /** @brief removes the first order  */
    void pop_front() noexcept { 
        qty_count_ -= front().qty;
        rb_.dequeue(); 
    }

    /** 
     * @brief returns the first order 
     * 
     * @return the first order at this price level
     * */
    [[nodiscard]] Order& front() noexcept { return rb_.peek(); } 
    [[nodiscard]] const Order& front() const noexcept { return rb_.peek(); }

    Order* back_ptr() noexcept { return rb_.back_ptr(); }

    /** @brief returns the total number of orders */
    uint64_t order_count() const noexcept { return rb_.item_count(); }


    /** @brief returns the total number of shares */
    uint64_t total_shares() const noexcept { return qty_count_; }

    /** 
     * @brief check if there are no orders
     * 
     * @return 1 if there are no orders, else 0 
     */
    uint8_t empty() const noexcept { return rb_.empty(); }

    /** 
     * @brief check if no more orders can be pushed back 
     * 
     * @return 1 if no more orders can be added, else 0
     */
    uint8_t full() const noexcept { return rb_.full(); }

    friend std::ostream& operator<<(std::ostream& os, const PriceLevel& pl) {
        os << "Total number of shares: " << pl.qty_count_ << "\n";
        os << pl.rb_ << "\n"; 
        return os;
    }

private:
    RingBuffer<Order, Config::ORDERBOOK_PRICE_LVL_RING_BUF_SIZE> rb_;
    
};