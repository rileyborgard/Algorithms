add_executable(algolib_tests
    test_fenwick.cpp
    test_segtree.cpp
    test_treap.cpp
    test_rev_treap.cpp
    test_rev_aug_treap.cpp
    test_bit_vector.cpp
)

target_link_libraries(algolib_tests
    PRIVATE
        algolib
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(algolib_tests)
