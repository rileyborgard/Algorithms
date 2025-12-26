add_executable(algolib_tests
    treap_test.cpp
    rev_treap_test.cpp
    rev_aug_treap_test.cpp
)

target_link_libraries(algolib_tests
    PRIVATE
        algolib
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(algolib_tests)
