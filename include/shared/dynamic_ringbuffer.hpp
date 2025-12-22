#pragma once 

#include <cstdint>
#include <utility>
#include <stdexcept>
#include <ostream>

using std::int64_t, std::uint8_t;

template <typename T>
class DynamicRingBuffer {
public:

    DynamicRingBuffer() :
        buf_(new T[20]),
        size_(20),
        head_(0),
        tail_(0),
        item_count_(0) {}

    /**
     * @brief constructor to specify starting size of ring buffer
     * 
     * @param size the initialized size of the ring buffer
     */
    explicit DynamicRingBuffer(int size) :
        buf_(new T[size]),
        size_(size),
        head_(0),
        tail_(0),
        item_count_(0) {}

    ~DynamicRingBuffer() {
        delete[] buf_;
    };

    /**
     * @brief inserts an item into the ring buffer
     * 
     * @param item the item to insert into the ring buffer
     */
    void insert(T item) {

        if (item_count_ + 1 > size_) {
            resize_();
        }

        buf_[tail_] = std::move(item);
        tail_ = (tail_ + 1) % size_;
        ++item_count_;
    }   

    /** 
     * @brief removes and returns the item from the ring buffer
     * 
     * @return T the item removed from the ring buffer
     */
    T dequeue() {
        if (empty()) throw std::logic_error("buffer is empty, no items to deque");
        T item = std::move(buf_[head_]);
        head_ = (head_ + 1) % size_;
        --item_count_;
        return item;
    }

    /**
     * @brief buffer contains items or not
     * 
     * @return 1 if the buffer is empty else 0
     */
    uint8_t empty() const {
        return (item_count_ == 0);
    }

    /**
     * @brief returns a pointer to the underlying array 
     * 
     * @return a pointer to beginning of the underlying array
     */
    const T* buffer() const {
        return buf_;
    }

    /**
     * @brief returns the number of items currently in the buffer
     */
    uint64_t items() const {
        return item_count_;
    }

    /**
     * @brief returns the size of the underlying array in the buffer
     */
    uint64_t capacity() const {
        return size_;
    }

    /**
     * @brief returns a pointer to beginning of the underlying array.
     * Note that the underlying array may contain data that was previously 
     * dequeued from the ring buffer.
     */
    T* begin() const {
        return &buf_[0];
    }

    /**
     * @brief returns a pointer to the ned of the underlying array.
     * Note that the underlying array may contain data that was previously
     * dequeued from the ring buffer
     */
    T* end() const {
        return &buf_[size_];
    }
    
    friend std::ostream& operator<<(std::ostream& os, const DynamicRingBuffer& drb) {
        for(uint64_t i{}; i < drb.item_count_; ++i) {
            os << drb.buf_[(drb.head_ + i) % drb.size_] << " ";
        }
        return os;
    }

    // TODO: implement shrink method to shrink underlying array to item count
    void shrink();


private:

    T* buf_;
    uint64_t size_; 
    uint64_t head_;
    uint64_t tail_;
    uint64_t item_count_;

    /**
     * @brief resizes the underlying array if the ring buffer is full 
     */
    void resize_() {
        T* new_arr = new T[size_ * 2];

        for(uint64_t i{}; i < item_count_; ++i) {
            new_arr[i] = std::move(buf_[(head_ + i) % size_]);
        }

        delete[] buf_;
        buf_ = new_arr;
        size_ *= 2;
        head_ = 0;
        tail_ = item_count_;
    }
};