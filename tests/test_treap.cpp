
#include <cassert>
#include <random>
#include <vector>
#include <chrono>
#include <climits>
#include "data-structures/treap.h"
#include "gtest/gtest.h"

TEST(TreapTest, Basic) {
    treap<int> T;
    using node = treap<int>::node;

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
