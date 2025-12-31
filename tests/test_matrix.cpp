
#include <vector>
#include <cassert>
#include <span>
#include <iostream>
#include <cmath>
#include "algebra/matrix.h"
#include "gtest/gtest.h"

TEST(SliceTest, BasicAccess) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    Slice<int> s(a.data() + 1, 3, 1);
    EXPECT_EQ(s.size(), 3u);
    EXPECT_EQ(s[0], 2);
    EXPECT_EQ(s[1], 3);
    EXPECT_EQ(s[2], 4);
}

TEST(SliceTest, StridedAccess) {
    std::vector<int> a = {1, 2, 3, 4, 5, 6};
    Slice<int> s(a.data(), 3, 2);
    EXPECT_EQ(s[0], 1);
    EXPECT_EQ(s[1], 3);
    EXPECT_EQ(s[2], 5);
}

TEST(SliceTest, IteratorWorks) {
    std::vector<int> a = {1, 2, 3, 4};
    Slice<int> s(a.data(), 4);
    int sum = 0;
    for (int x : s) sum += x;
    EXPECT_EQ(sum, 10);
}

TEST(VectorTest, ConstructionFromSlice) {
    std::vector<int> a = {1, 2, 3, 4};
    Slice<int> s(a.data() + 1, 2);
    Vector<int> v(s);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Arithmetic) {
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {3, 2, 1};
    EXPECT_EQ(a + b, Vector<int>({4, 4, 4}));
    EXPECT_EQ(a - b, Vector<int>({-2, 0, 2}));
    EXPECT_EQ(a * 2, Vector<int>({2, 4, 6}));
}

TEST(VectorTest, DotAndNorm) {
    Vector<double> v = {3, 4};
    EXPECT_DOUBLE_EQ(v.dot(v), 25.0);
    EXPECT_DOUBLE_EQ(v.norm(), 5.0);
}

TEST(VectorTest, Normalize) {
    Vector<double> v = {3, 4};
    auto u = v.normalized();
    EXPECT_NEAR(u.norm(), 1.0, 1e-12);
}

TEST(MatrixTest, BasicConstruction) {
    Matrix<int> m(2, 3, 7);
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 3; j++)
            EXPECT_EQ(m(i, j), 7);
}

TEST(MatrixTest, InitializerList) {
    Matrix<int> m = {{1, 2}, {3, 4}};
    EXPECT_EQ(m.height(), 2u);
    EXPECT_EQ(m.width(), 2u);
    EXPECT_EQ(m(1, 0), 3);
}

TEST(MatrixTest, Identity) {
    auto I = Matrix<int>::identity(3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            EXPECT_EQ(I(i, j), i == j);
}

TEST(MatrixTest, RowAndColSlices) {
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}};
    auto r = m.row(1);
    auto c = m.col(2);
    EXPECT_EQ(r[0], 4);
    EXPECT_EQ(r[1], 5);
    EXPECT_EQ(r[2], 6);
    EXPECT_EQ(c[0], 3);
    EXPECT_EQ(c[1], 6);
}

TEST(MatrixTest, MatrixVectorMultiply) {
    Matrix<int> m = {{1, 2}, {3, 4}};
    Vector<int> v = {5, 6};
    Vector<int> r = m * Slice<int>(v.data(), v.size());
    Vector<int> r2 = m * v;
    EXPECT_EQ(r, Vector<int>({17, 39}));
    EXPECT_EQ(r2, Vector<int>({17, 39}));
}

TEST(MatrixTest, VectorMatrixMultiply) {
    Matrix<int> m = {{1, 2}, {3, 4}};
    Vector<int> v = {5, 6};
    Vector<int> r = Slice<int>(v.data(), v.size()) * m;
    Vector<int> r2 = v * m;
    EXPECT_EQ(r, Vector<int>({23, 34}));
    EXPECT_EQ(r2, Vector<int>({23, 34}));
}

TEST(MatrixTest, MatrixMatrixMultiply) {
    Matrix<int> a = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int> b = {{7, 8}, {9, 10}, {11, 12}};
    Matrix<int> c = a * b;
    EXPECT_EQ(c.height(), 2u);
    EXPECT_EQ(c.width(), 2u);
    EXPECT_EQ(c(0, 0), 58);
    EXPECT_EQ(c(0, 1), 64);
    EXPECT_EQ(c(1, 0), 139);
    EXPECT_EQ(c(1, 1), 154);
}

TEST(MatrixTest, Transpose) {
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}};
    auto t = m.transpose();
    EXPECT_EQ(t.height(), 3u);
    EXPECT_EQ(t.width(), 2u);
    EXPECT_EQ(t(2, 1), 6);
}

TEST(MatrixTest, Arithmetic) {
    Matrix<int> a = {{1, 2}, {3, 4}};
    Matrix<int> b = {{4, 3}, {2, 1}};
    EXPECT_EQ((a + b)(0, 0), 5);
    EXPECT_EQ((a - b)(1, 1), 3);
    EXPECT_EQ((a * 2)(1, 0), 6);
}
