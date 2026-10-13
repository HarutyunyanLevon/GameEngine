include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.4.11
  GIT_SHALLOW TRUE
  SYSTEM
)
FetchContent_MakeAvailable(doctest)

# Every test_*.cpp in this folder is picked up automatically (re-run cmake is not needed).
# Add a file per exercise, e.g. test_buffer.cpp on Day 1, test_pool_allocator.cpp on Day 6.
file(GLOB ENGINE_TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_*.cpp)

add_executable(engine_tests ${ENGINE_TEST_SOURCES})
target_link_libraries(engine_tests PRIVATE engine::engine doctest::doctest)

add_test(NAME engine_tests COMMAND engine_tests)
