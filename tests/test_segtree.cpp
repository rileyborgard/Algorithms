
#include <functional>
#include <vector>
#include <cassert>
#include "data-structures/segtree.h"
#include "gtest/gtest.h"

TEST(SegtreeTest, IntGetAdd) {
    Segtree<int, std::plus<int>> tree(10, 0);
    ASSERT_EQ(tree.query(0, 5), 0);
    tree.set(8, 1);
    tree.set(1, 1);
    tree.set(3, 1);
    tree.set(7, 1);
    ASSERT_EQ(tree.query(0, 0), 0);
    ASSERT_EQ(tree.query(0, 1), 0);
    ASSERT_EQ(tree.query(0, 2), 1);
    ASSERT_EQ(tree.query(0, 3), 1);
    ASSERT_EQ(tree.query(0, 4), 2);
    ASSERT_EQ(tree.query(0, 5), 2);
    ASSERT_EQ(tree.query(0, 6), 2);
    ASSERT_EQ(tree.query(0, 7), 2);
    ASSERT_EQ(tree.query(0, 8), 3);
    ASSERT_EQ(tree.query(0, 9), 4);
}
