
#include <cassert>
#include <random>
#include <vector>
#include <chrono>
#include <climits>
#include "gtest/gtest.h"
#include "data-structures/rev_aug_treap.h"

TEST(RevAugTreapTest, Basic) {
    rev_aug_treap<int, std::plus<int>> T(0);
    using node = rev_aug_treap<int, std::plus<int>>::node;

    int n = 800000;
    std::vector<int> ve(n, 0);
    std::mt19937 rng(1);
    auto rand = [&](int l, int r) {
        std::uniform_int_distribution<int> uni(l, r);
        return uni(rng);
    };
    for (int i = 0; i < n; i++) {
        ve[i] = rand(0, 1000);
    }
    std::sort(ve.begin(), ve.end());

    std::vector<node*> nodes;
    for (int i = 0; i < ve.size(); i++) {
        nodes.push_back(T.make(ve[i]));
    }
    node* root = T.join(nodes);

    std::vector<int> clone;
    T.for_each(root, [&](node* u) {
        clone.push_back(u->value);
    });
    assert(clone == ve);

    for (int i = 0; i < ve.size(); i++) {
        assert(T.at(root, i)->value == ve[i]);
    }

    assert(root->p == nullptr);
    for (int i = 0; i < nodes.size(); i++) {
        assert(T.root(nodes[i]) == root);
        assert(T.index_of(nodes[i]) == i);
    }

    int k = n / 3;
    auto [l, r] = T.split(root, k);

    assert(T.size_of(l) == k);
    assert(T.size_of(r) == n - k);
    assert(l->p == nullptr);
    assert(r->p == nullptr);

    int cnt_l = 0, cnt_r = 0;
    T.for_each(l, [&](node* u) {
        assert(T.root(u) == l);
        cnt_l++;
    });
    T.for_each(r, [&](node* u) {
        assert(T.root(u) == r);
        cnt_r++;
    });
    assert(cnt_l == T.size_of(l));
    assert(cnt_r == T.size_of(r));

    root = T.join(l, r);
    assert(T.size_of(root) == n);
    assert(root->p == nullptr);

    auto [u, cnt] = T.lower_bound(root, [&](node* x) {
        return x->value < 5;
    });

    if (u) {
        assert(u->value >= 5);
    }

    std::tie(l, r) = T.split(root, cnt);
    T.for_each(l, [&](node* x) {
        assert(x->value < 5);
    });
    T.for_each(r, [&](node* x) {
        assert(x->value >= 5);
    });
}

TEST(RevAugTreapTest, Rev) {
    rev_aug_treap<int, std::plus<int>> T(0);
    using node = rev_aug_treap<int, std::plus<int>>::node;

    int n = 800000;
    std::vector<int> ve(n, 0);
    std::mt19937 rng(1);
    auto rand = [&](int l, int r) {
        std::uniform_int_distribution<int> uni(l, r);
        return uni(rng);
    };
    for (int i = 0; i < n; i++) {
        ve[i] = rand(0, 1000);
    }
    std::sort(ve.begin(), ve.end());

    std::vector<node*> nodes;
    for (int i = 0; i < ve.size(); i++) {
        nodes.push_back(T.make(ve[i]));
    }
    node* root = T.join(nodes);

    T.flip(root);
    std::vector<int> clone;
    T.for_each(root, [&](node* x) {
        clone.push_back(x->value);
    });
    std::reverse(clone.begin(), clone.end());
    assert(ve == clone);

    T.flip(root);
    for (int i = 0; i < n; i++) {
        assert(T.index_of(nodes[i]) == i);
    }

    T.flip(root);
    for (int i = 0; i < n; i++) {
        assert(T.at(root, i) == nodes[n - i - 1]);
    }
}

TEST(RevAugTreapTest, Aug) {
    struct monoid {
        int cnt;
        long long sum;
        long long sum_i;
        monoid() : cnt(0), sum(0), sum_i(0) {}
        monoid(long long x) : cnt(1), sum(x), sum_i(0) {}
        monoid operator+(const monoid& o) const {
            monoid M;
            M.cnt = cnt + o.cnt;
            M.sum = sum + o.sum;
            M.sum_i = sum_i + o.sum_i + o.sum * cnt;
            return M;
        }
        monoid operator~() const {
            // Flip operation
            monoid M;
            M.cnt = cnt;
            M.sum = sum;
            // sum_i a_{cnt - i - 1} * i
            // = sum_i a_i (cnt - i - 1)
            // = - (sum_i a_i * i) + (cnt - 1) * sum_i a_i
            M.sum_i = sum * (cnt - 1) - sum_i;
            return M;
        }
    };
    rev_aug_treap<monoid, std::plus<monoid>, std::bit_not<monoid>> T(monoid{});
    using node = decltype(T)::node;
    std::vector<node*> nodes;
    std::vector<int> ve = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < ve.size(); i++) {
        nodes.push_back(T.make(ve[i]));
    }
    node* root = T.join(nodes);
    // Expect 0*0 + 1*1 + 2*2 + 3*3 + 4*4 + 5*5 = 55
    assert(T.aug(root).sum_i == 55);
    T.flip(root);
    // Expect 5*0 + 4*1 + 3*2 + 2*3 + 1*4 + 0*5 = 20
    assert(T.aug(root).sum_i == 20);

    assert(T.query(root, 0, 6).sum_i == 20);

    // [5, 4, 3, 2, 1, 0]
    // 4*0 + 3*1 + 2*2 + 1*3 = 10
    assert(T.query(root, 1, 5).sum_i == 10);

    T.flip(root);
    assert(T.aug(root).sum_i == 55);
}
