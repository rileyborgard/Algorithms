
#include <random>
#include <vector>
#include <bitset>
#include <cassert>
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

static void BM_BitVectorSubsetSumPreallocate(benchmark::State& state) {
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
        BitVector vec2(n);
        vec.set(0, true);
        int ans = 0;
        for (int val : vals) {
            vec.left_shift(val, vec2);
            vec |= vec2;
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
    ->Range(1 << 8, 1 << 18)->Unit(benchmark::kMillisecond);

BENCHMARK(BM_BitVectorSubsetSumPreallocate)
    ->Range(1 << 8, 1 << 18)->Unit(benchmark::kMillisecond);

#define BITSET_BENCH(N) BENCHMARK(BM_BitsetSubsetSum<N>) \
    ->Arg(N)->Unit(benchmark::kMillisecond);

BITSET_BENCH(256);
BITSET_BENCH(512);
BITSET_BENCH(4096);
BITSET_BENCH(32768);
BITSET_BENCH(262144);
