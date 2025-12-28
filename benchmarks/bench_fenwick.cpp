
#include <random>
#include <vector>
#include <iostream>
#include <cassert>
#include "data-structures/fenwick.h"
#include <benchmark/benchmark.h>

enum class FenwickOperationType {
    kAdd,
    kGet,
};

struct FenwickOperation {
    FenwickOperationType type;
    int i;
    int64_t x;
};

static void BM_FenwickUniform(benchmark::State& state) {
    int n = state.range(0) - 1;
    int m = n;
    std::vector<FenwickOperation> ops;
    std::mt19937 rng(1);
    std::uniform_int_distribution<int64_t> uni_val(-1e9, 1e9);
    std::uniform_int_distribution<int> uni_index(1, n);
    std::uniform_int_distribution<int> uni_op_type(1, 2);
    for (int i = 0; i < m; i++) {
        int type = uni_op_type(rng);
        if (type == 1) {
            ops.push_back({FenwickOperationType::kAdd, uni_index(rng), uni_val(rng)});
        } else {
            ops.push_back({FenwickOperationType::kGet, uni_index(rng), -1});
        }
    }

    int ops_processed = 0;
    for (auto _ : state) {
        Fenwick<int64_t> fenwick(n + 1);
        int sum = 0;
        for (const auto& op : ops) {
            if (op.type == FenwickOperationType::kAdd) {
                fenwick.add(op.i, op.x);
            } else {
                sum += fenwick.get(op.i);
            }
        }
        ops_processed += ops.size();
        benchmark::DoNotOptimize(sum);
    }

    state.counters["ops"] = benchmark::Counter(
        ops_processed, benchmark::Counter::kIsRate
    );
}

BENCHMARK(BM_FenwickUniform)
    ->Range(1 << 8, 1 << 22)->Unit(benchmark::kMillisecond);