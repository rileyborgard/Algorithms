
#include <random>
#include <vector>
#include <bitset>
#include "data-structures/bit_vector.h"
#include <benchmark/benchmark.h>

static void BM_BitVectorSubsetSum(benchmark::State& state) {
    int n = state.range(0);
    int m = n;
    std::mt19937 rng(1);
    std::uniform_int_distribution<int> uni_val(1, n);
    std::vector<int> vals(m);
    for (int i = 0; i < m; i++) {
        vals[i] = uni_val(rng);
    }

    for (auto _ : state) {
        BitVector vec(n);
        vec.set(0, true);
        int ans = 0;
        for (int val : vals) {
            vec |= (vec << val);
        }
        ans += vec.count();
        benchmark::DoNotOptimize(ans);
    }
}

template<int N>
static void BM_BitsetSubsetSum(benchmark::State& state) {
    int m = state.range(0);
    std::mt19937 rng(1);
    std::uniform_int_distribution<int> uni_val(1, N);
    std::vector<int> vals(m);
    for (int i = 0; i < m; i++) {
        vals[i] = uni_val(rng);
    }

    for (auto _ : state) {
        std::bitset<N> vec;
        vec.set(0, true);
        int ans = 0;
        for (int val : vals) {
            vec |= (vec << val);
        }
        ans += vec.count();
        benchmark::DoNotOptimize(ans);
    }
}

BENCHMARK(BM_BitVectorSubsetSum)
    ->Range(1 << 8, 1 << 16)->Unit(benchmark::kMillisecond);

BENCHMARK(BM_BitsetSubsetSum<256>)
    ->Arg(256)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BitsetSubsetSum<512>)
    ->Arg(512)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BitsetSubsetSum<4096>)
    ->Arg(4096)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BitsetSubsetSum<32768>)
    ->Arg(32768)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BitsetSubsetSum<65536>)
    ->Arg(65536)->Unit(benchmark::kMillisecond);