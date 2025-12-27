
#include <vector>
#include <cassert>
#include "data-structures/fenwick.h"
#include "gtest/gtest.h"

TEST(FenwickTest, IntGetAdd) {
    Fenwick<int> fenwick(10);
    ASSERT_EQ(fenwick.get(5), 0);
    fenwick.add(8, 1);
    fenwick.add(1, 1);
    fenwick.add(3, 1);
    fenwick.add(7, 1);
    ASSERT_EQ(fenwick.get(0), 0);
    ASSERT_EQ(fenwick.get(1), 1);
    ASSERT_EQ(fenwick.get(2), 1);
    ASSERT_EQ(fenwick.get(3), 2);
    ASSERT_EQ(fenwick.get(4), 2);
    ASSERT_EQ(fenwick.get(5), 2);
    ASSERT_EQ(fenwick.get(6), 2);
    ASSERT_EQ(fenwick.get(7), 3);
    ASSERT_EQ(fenwick.get(8), 4);
    ASSERT_EQ(fenwick.get(9), 4);
}

TEST(FenwickTest, IntLowerBound) {
    Fenwick<int> fenwick(10);
    ASSERT_EQ(fenwick.get(5), 0);
    fenwick.add(8, 1);
    fenwick.add(1, 1);
    fenwick.add(3, 1);
    fenwick.add(7, 1);
    ASSERT_EQ(fenwick.lower_bound(0), 1);
    ASSERT_EQ(fenwick.lower_bound(1), 1);
    ASSERT_EQ(fenwick.lower_bound(2), 3);
    ASSERT_EQ(fenwick.lower_bound(3), 7);
    ASSERT_EQ(fenwick.lower_bound(4), 8);
    ASSERT_EQ(fenwick.lower_bound(5), 10);
}