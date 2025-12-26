add_executable(algolib_benchmarks
    bench_dsu.cpp
)

target_link_libraries(algolib_benchmarks
    PRIVATE
        algolib
        benchmark::benchmark
        benchmark::benchmark_main
)
