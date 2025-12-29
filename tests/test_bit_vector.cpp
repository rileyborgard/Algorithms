
#include <random>
#include <bitset>
#include <vector>
#include "data-structures/bit_vector.h"
#include "gtest/gtest.h"

template <int N>
static void test_bit_vector_subset_sum(int m) {
    BitVector vec(N);
    std::bitset<N> bs;
    std::mt19937 rng(1);
    std::uniform_int_distribution<int> uni_val(1, N);
    std::vector<int> vals(m);
    for (int i = 0; i < m; i++) {
        vals[i] = uni_val(rng);
    }

    vec.set(0);
    bs.set(0);

    for (int val : vals) {
        vec |= (vec << val);
        bs |= (bs << val);
    }

    for (int i = 0; i < N; i++) {
        ASSERT_EQ(vec.test(i), bs.test(i));
    }
}

TEST(BitVectorTest, SubsetSum) {
    test_bit_vector_subset_sum<10>(100);
    test_bit_vector_subset_sum<63>(100);
    test_bit_vector_subset_sum<64>(100);
    test_bit_vector_subset_sum<65>(100);
    test_bit_vector_subset_sum<100>(100);
    test_bit_vector_subset_sum<127>(100);
    test_bit_vector_subset_sum<128>(100);
    test_bit_vector_subset_sum<129>(100);
    test_bit_vector_subset_sum<1000>(1000);
}