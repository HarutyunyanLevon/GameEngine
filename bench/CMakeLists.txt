include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
# A newer compiler than the one Benchmark was tested with can add warnings; do not fail on them.
set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.1
  GIT_SHALLOW TRUE
  SYSTEM
)
FetchContent_MakeAvailable(benchmark)

# Every bench_*.cpp in this folder is picked up automatically.
# Add a file per experiment, e.g. bench_aos_vs_soa.cpp on Day 5.
file(GLOB ENGINE_BENCH_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bench_*.cpp)

add_executable(engine_bench ${ENGINE_BENCH_SOURCES})
target_link_libraries(engine_bench PRIVATE engine::engine benchmark::benchmark)
