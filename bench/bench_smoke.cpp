#include <cstddef>
#include <numeric>
#include <vector>

#include <benchmark/benchmark.h>

#include "engine/core/Types.h"

static void BM_SumVector(benchmark::State& state) {
    const auto count = static_cast<std::size_t>(state.range(0));
    std::vector<engine::u64> values(count, 1);

    for (auto _ : state) {
        engine::u64 sum = std::accumulate(values.begin(), values.end(), engine::u64{0});
        benchmark::DoNotOptimize(sum);
    }

    state.SetBytesProcessed(static_cast<engine::i64>(state.iterations()) * state.range(0) *
                            static_cast<engine::i64>(sizeof(engine::u64)));
}
BENCHMARK(BM_SumVector)->RangeMultiplier(8)->Range(1 << 10, 1 << 22);

static void BM_PushBackNoReserve(benchmark::State& state) {
    const auto count = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::vector<engine::u32> v;
        for (std::size_t i = 0; i < count; ++i) v.push_back(static_cast<engine::u32>(i));
        benchmark::DoNotOptimize(v.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_PushBackNoReserve)->Arg(1 << 10)->Arg(1 << 16);

static void BM_PushBackReserved(benchmark::State& state) {
    const auto count = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::vector<engine::u32> v;
        v.reserve(count);
        for (std::size_t i = 0; i < count; ++i) v.push_back(static_cast<engine::u32>(i));
        benchmark::DoNotOptimize(v.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_PushBackReserved)->Arg(1 << 10)->Arg(1 << 16);
