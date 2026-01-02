
#include <vector>
#include "utils/next_array.h"
#include "gtest/gtest.h"

TEST(NextArrayTest, Basic) {
    std::vector<int> vec = {0, 0, 0};
    std::vector<std::vector<int>> res;
    do {
        res.push_back(vec);
    } while (next_array(vec.begin(), vec.end(), 2));

    std::vector<std::vector<int>> expected = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1},
    };

    ASSERT_EQ(res, expected);
}

TEST(NextArrayTest, MaxVector) {
    std::vector<int> vec = {0, 0, 0};
    std::vector<std::vector<int>> res;
    std::vector<int> mx = {2, 3, 2};
    do {
        res.push_back(vec);
    } while (next_array_vec(vec.begin(), vec.end(), mx));

    std::vector<std::vector<int>> expected = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
        {0, 2, 0},
        {0, 2, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1},
        {1, 2, 0},
        {1, 2, 1},
    };

    ASSERT_EQ(res, expected);
}
