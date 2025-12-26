
#include <random>
#include <vector>
#include "data-structures/dsu.h"
#include <benchmark/benchmark.h>

static void BM_DSU_Uniform(benchmark::State& state) {
    int n = state.range(0);
    int m = state.range(1);
    std::vector<std::pair<int, int>> pairs(m);
    std::mt19937 rng(1);
    std::uniform_int_distribution<int> uni(0, n - 1);
    for (int i = 0; i < m; i++) {
        pairs[i] = {uni(rng), uni(rng)};
    }
    for (auto _ : state) {
        dsu D(n);
        int sum = 0;
        for (const auto& [u, v] : pairs) {
            sum += D.join(u, v);
        }
        benchmark::DoNotOptimize(sum);
    }
}

static void LinkedArgs(benchmark::internal::Benchmark* b) {
    int mult = 4;
    for (int i = 4; i <= (1 << 20); i *= mult) {
        b->Args({i, i});
    }
}

BENCHMARK(BM_DSU_Uniform)
    ->Apply(LinkedArgs)
    ->Args({1 << 10, 1 << 20})
    ->Args({1 << 20, 1 << 10});
