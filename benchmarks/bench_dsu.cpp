
#include <random>
#include <vector>
#include "data-structures/dsu.h"
#include <benchmark/benchmark.h>
#include <iostream>

static void BM_DSU_Uniform(benchmark::State& state) {
    int n = state.range(0);
    int m = n;
    std::vector<std::pair<int, int>> pairs(m);
    std::mt19937 rng(1);
    std::uniform_int_distribution<int> uni(0, n - 1);
    for (int i = 0; i < m; i++) {
        pairs[i] = {uni(rng), uni(rng)};
    }
    int ops_processed = 0;
    int iterations = 0;
    for (auto _ : state) {
        iterations++;
        DSU D(n);
        int sum = 0;
        for (const auto& [u, v] : pairs) {
            sum += D.join(u, v);
        }
        ops_processed += pairs.size();
        benchmark::DoNotOptimize(sum);
    }

    state.counters["ops"] = benchmark::Counter(
        ops_processed, benchmark::Counter::kIsRate
    );
}

BENCHMARK(BM_DSU_Uniform)
    ->Range(1 << 8, 1 << 22);


struct DSU2 {
    std::vector<int> a;
    DSU2(int n) : a(n, -1) {}
    int depth(int x) {
        return a[x] < 0 ? 0 : 1 + depth(a[x]);
    }
    int constfind(int x) {
        return a[x] < 0 ? x : find(a[x]);
    }
    int find(int x) {
        return a[x] < 0 ? x : a[x] = find(a[x]);
    }
    int size(int x) {
        return -a[find(x)];
    }
    bool join(int x, int y) {
        if((x = find(x)) == (y = find(y))) return false;
        if(a[x] > a[y]) std::swap(x, y);
        a[x] += a[y];
        a[y] = x;
        return true;
    }
};


enum class DSUOperationType {
    kJoin = 0,
    kFind = 1,
};

struct DSUOperation {
    DSUOperationType type;
    int x;
    int y;
};

struct WorstCaseGenerator {
    DSU2 sim;
    std::vector<int> nodes;
    std::vector<DSUOperation> ops;

    WorstCaseGenerator(int n) : sim(n) {
        nodes.resize(n);
        std::iota(nodes.begin(), nodes.end(), 0);
    }

    void apply(const DSUOperation& op) {
        ops.push_back(op);
        if (op.type == DSUOperationType::kJoin) {
            sim.join(op.x, op.y);
        } else {
            sim.find(op.x);
        }
    }

    int build(int k, const std::vector<int>& current_nodes) {
        if (current_nodes.empty()) return -1;

        if (k == 0 || current_nodes.size() <= 2) {
            int root = current_nodes[0];
            for (size_t i = 1; i < current_nodes.size(); ++i) {
                apply(DSUOperation{DSUOperationType::kJoin, current_nodes[i - 1], current_nodes[i]});
            }
            return sim.find(root);
        }

        size_t mid = current_nodes.size() / 2;
        std::vector<int> left_part(current_nodes.begin(), current_nodes.begin() + mid);
        std::vector<int> right_part(current_nodes.begin() + mid, current_nodes.end());

        int root_left = build(k - 1, left_part);
        int root_right = build(k - 1, right_part);

        auto deepest = [&](const std::vector<int>& nodes) -> int {
            int depth = -1;
            int best = -1;
            for (int node : nodes) {
                int d = sim.depth(node);
                if (d > depth) {
                    depth = d;
                    best = node;
                }
            }
            return best;
        };

        if (root_left != -1 && root_right != -1) {
            apply(DSUOperation{DSUOperationType::kJoin, deepest(left_part), deepest(right_part)});
        }

        return sim.constfind(root_left); 
    }
    
    std::vector<DSUOperation> generate(int k_level) {
        ops.clear();
        build(k_level, nodes);
        return ops;
    }
};

static void BM_DSU_Adversary(benchmark::State& state) {
    int n = state.range(0);

    const int K = log2(n);
    WorstCaseGenerator gen(n);
    std::vector<DSUOperation> ops = gen.generate(K);

    std::mt19937 rng(1);
    std::vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    std::shuffle(perm.begin(), perm.end(), rng);
    for (auto& op : ops) {
        op.x = op.x == -1 ? -1 : perm[op.x];
        op.y = op.y == -1 ? -1 : perm[op.y];
    }

    long long ops_processed = 0;
    int iterations = 0;

    for (auto _ : state) {
        iterations++;
        DSU D(n);
        int sum = 0;
        for (const auto& op : ops) {
            if (op.type == DSUOperationType::kJoin) {
                sum += D.join(op.x, op.y);
            } else {
                sum += D.find(op.x);
            }
        }
        ops_processed += ops.size();
        benchmark::DoNotOptimize(sum);
    }

    state.counters["ops"] = benchmark::Counter(
        ops_processed, benchmark::Counter::kIsRate
    );
}

BENCHMARK(BM_DSU_Adversary)
    ->Range(1 << 8, 1 << 22);