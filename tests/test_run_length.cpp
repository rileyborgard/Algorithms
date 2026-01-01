
#include <vector>
#include "utils/run_length.h"
#include "gtest/gtest.h"

TEST(RunLengthTest, Basic) {
    std::string str = "aaaccbbbxyaa";
    std::vector<std::pair<char, int>> runs = run_length(str.begin(), str.end());
    std::vector<std::pair<char, int>> expected = {
        {'a', 3},
        {'c', 2},
        {'b', 3},
        {'x', 1},
        {'y', 1},
        {'a', 2},
    };
    ASSERT_EQ(runs, expected);
}