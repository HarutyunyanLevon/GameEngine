cmake_minimum_required(VERSION 3.25)
project(mini_engine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to RelWithDebInfo so a plain `cmake -B build` is benchmark-friendly.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

option(ENGINE_ASAN "Enable AddressSanitizer + UndefinedBehaviorSanitizer" OFF)
option(ENGINE_TSAN "Enable ThreadSanitizer (cannot be combined with ENGINE_ASAN)" OFF)
option(ENGINE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(ENGINE_BUILD_TESTS "Build unit tests" ON)
option(ENGINE_BUILD_BENCH "Build benchmarks" ON)
option(ENGINE_BUILD_SANDBOX "Build the sandbox executable" ON)

if(ENGINE_ASAN AND ENGINE_TSAN)
  message(FATAL_ERROR "ENGINE_ASAN and ENGINE_TSAN cannot be enabled together.")
endif()

include(cmake/EngineOptions.cmake)

add_subdirectory(engine)

if(ENGINE_BUILD_SANDBOX)
  add_subdirectory(sandbox)
endif()

if(ENGINE_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(ENGINE_BUILD_BENCH)
  if(ENGINE_ASAN OR ENGINE_TSAN)
    message(WARNING "Sanitizers distort timings. Use the 'release' preset for benchmarks.")
  endif()
  add_subdirectory(bench)
endif()
