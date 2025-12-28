
#include <random>
#include <cassert>
#include "data-structures/segtree.h"
#include <benchmark/benchmark.h>

enum class SegtreeOperationType {
    kSet,
    kQuery,
    kAdd,
};

struct SegtreeOperation {
    SegtreeOperationType type;
    int l;
    int r;
    int k;
    int64_t x;
};

static void BM_SegtreeUniformSetQuery(benchmark::State& state) {
    int n = state.range(0);
    int m = n;
    std::vector<SegtreeOperation> ops;
    std::mt19937 rng(1);
    std::uniform_int_distribution<int64_t> uni_val(-1e9, 1e9);
    std::uniform_int_distribution<int> uni_index(0, n - 1);
    std::uniform_int_distribution<int> uni_op_type(1, 2);

    for (int i = 0; i < m; i++) {
        int type = uni_op_type(rng);
        if (type == 1) {
            int k = uni_index(rng);
            int64_t x = uni_val(rng);
            ops.push_back({SegtreeOperationType::kSet, -1, -1, k, x});
        } else {
            int l = uni_index(rng);
            int r = uni_index(rng);
            if (l > r) std::swap(l, r);
            r++;
            ops.push_back({SegtreeOperationType::kQuery, l, r, -1, -1});
        }
    }

    int ops_processed = 0;
    for (auto _ : state) {
        int64_t sum = 0;
        Segtree<int64_t, std::plus<int64_t>> tree(n, 0LL);

        for (const auto& op : ops) {
            if (op.type == SegtreeOperationType::kSet) {
                tree.set(op.k, op.x);
            } else {
                sum += tree.query(op.l, op.r);
            }
        }
        ops_processed += ops.size();
        benchmark::DoNotOptimize(sum);
    }

    state.counters["ops"] = benchmark::Counter(
        ops_processed, benchmark::Counter::kIsRate
    );
}

static void BM_SegtreeUniformAddQuery(benchmark::State& state) {
    int n = state.range(0);
    int m = n;
    std::vector<SegtreeOperation> ops;
    std::mt19937 rng(1);
    std::uniform_int_distribution<int64_t> uni_val(-1e9, 1e9);
    std::uniform_int_distribution<int> uni_index(0, n - 1);
    std::uniform_int_distribution<int> uni_op_type(1, 2);

    for (int i = 0; i < m; i++) {
        int type = uni_op_type(rng);
        if (type == 1) {
            int k = uni_index(rng);
            int64_t x = uni_val(rng);
            ops.push_back({SegtreeOperationType::kAdd, -1, -1, k, x});
        } else {
            int l = uni_index(rng);
            int r = uni_index(rng);
            if (l > r) std::swap(l, r);
            r++;
            ops.push_back({SegtreeOperationType::kQuery, l, r, -1, -1});
        }
    }

    int ops_processed = 0;
    for (auto _ : state) {
        int64_t sum = 0;
        Segtree<int64_t, std::plus<int64_t>> tree(n, 0LL);

        for (const auto& op : ops) {
            if (op.type == SegtreeOperationType::kAdd) {
                tree.add(op.k, op.x);
            } else {
                sum += tree.query(op.l, op.r);
            }
        }
        ops_processed += ops.size();
        benchmark::DoNotOptimize(sum);
    }

    state.counters["ops"] = benchmark::Counter(
        ops_processed, benchmark::Counter::kIsRate
    );
}

BENCHMARK(BM_SegtreeUniformSetQuery)
    ->Range(1 << 8, 1 << 22)->Unit(benchmark::kMillisecond);

BENCHMARK(BM_SegtreeUniformAddQuery)
    ->Range(1 << 8, 1 << 22)->Unit(benchmark::kMillisecond);
