#include <benchmark/benchmark.h>
#include <shared/dynamic_ringbuffer.hpp>
#include <shared/ringbuffer.hpp>
#include <deque>

static void BM_DRB_enqueue(benchmark::State& state) {
    DynamicRingBuffer<int> drb;
    for (auto _ : state) {
        drb.enqueue(5);
        drb.dequeue();
    }
}
BENCHMARK(BM_DRB_enqueue);

static void BM_RB_ENQUEUE_DEQUEUE(benchmark::State& state) {
    RingBuffer<int, 10> rb;
    for (auto _ : state) {
        rb.enqueue(5);
        rb.dequeue();
    }
}
BENCHMARK(BM_RB_ENQUEUE_DEQUEUE);

static void BM_DQ_ENQUEUE_DEQUEUE(benchmark::State& state) {
    std::deque<int> dq;
    for (auto _ : state) {
        dq.push_back(5);
        dq.pop_front();
    }
}
BENCHMARK(BM_DQ_ENQUEUE_DEQUEUE);

BENCHMARK_MAIN();