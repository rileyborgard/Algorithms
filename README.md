Algorithms

This repository contains a collection of algorithm implementations and small utilities aimed at competitive programming and algorithm practice. It includes implementations, unit tests, and benchmarks so you can build, test, and measure performance locally.

The code is organized roughly like this:

- include/        — public headers and reusable components
- source/         — algorithm implementations and library code
- tests/          — unit tests (GoogleTest)
- benchmarks/     — microbenchmarks (Google Benchmark)
- cmake/          — CMake helper modules

Quick start (Linux / macOS)

1. Requirements
   - CMake 3.20 or newer
   - A C++17-compatible compiler (GCC, Clang, or MSVC)
   - Git

2. Build
   ```bash
   git clone https://github.com/<your-username>/Algorithms.git
   cd Algorithms
   mkdir -p build
   cd build
   cmake ..
   cmake --build . -- -j$(nproc)
   ```

3. Run tests
   From the build directory run:
   ```bash
   ctest --output-on-failure -j$(nproc)
   ```
   Or run a test binary directly (example):
   ```bash
   ./tests/algolib_tests
   ```

4. Run benchmarks
   Build the benchmark target and run the resulting binary. Exact target name may vary; the repository uses CMake FetchContent to pull Google Benchmark.
   ```bash
   # from build/
   cmake --build . --target algolib_benchmarks
   ./benchmarks/algolib_benchmarks
   ```

Notes
- The project fetches test and benchmark dependencies via CMake, so you generally don't have to install GoogleTest or Google Benchmark system-wide.
- If you hit issues with CMake or your compiler, make sure your toolchain meets the version requirements and that your build tools are on PATH.

Contributing
- Feel free to open issues or PRs with fixes or new algorithms. Keep tests updated and add small benchmarks where appropriate.