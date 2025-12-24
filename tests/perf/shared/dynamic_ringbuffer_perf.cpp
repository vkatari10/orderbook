#include <benchmark/benchmark.h>
#include <shared/dynamic_ringbuffer.hpp>

static void BM_DRB_enqueue(benchmark::State& state) {
    DynamicRingBuffer<int> drb;
    for (auto _ : state) drb.enqueue(5);
}
BENCHMARK(BM_DRB_enqueue);

static void BM_DRB_creation(benchmark::State& state) {
    for (auto _ : state) DynamicRingBuffer<int> drb;
}
BENCHMARK(BM_DRB_creation);

BENCHMARK_MAIN();