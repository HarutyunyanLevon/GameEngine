#pragma once

#include "engine/core/Assert.h"

// Detect sanitizers for both GCC (__SANITIZE_*) and Clang (__has_feature).
#define ENGINE_HAS_ASAN 0
#define ENGINE_HAS_TSAN 0

#if defined(__SANITIZE_ADDRESS__)
#undef ENGINE_HAS_ASAN
#define ENGINE_HAS_ASAN 1
#endif
#if defined(__SANITIZE_THREAD__)
#undef ENGINE_HAS_TSAN
#define ENGINE_HAS_TSAN 1
#endif
#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#undef ENGINE_HAS_ASAN
#define ENGINE_HAS_ASAN 1
#endif
#if __has_feature(thread_sanitizer)
#undef ENGINE_HAS_TSAN
#define ENGINE_HAS_TSAN 1
#endif
#endif

namespace engine {

[[nodiscard]] constexpr const char* compilerName() noexcept {
#if defined(__clang__)
    return "clang " __clang_version__;
#elif defined(__GNUC__)
    return "gcc " __VERSION__;
#elif defined(_MSC_VER)
    return "msvc";
#else
    return "unknown";
#endif
}

[[nodiscard]] constexpr bool hasAddressSanitizer() noexcept { return ENGINE_HAS_ASAN != 0; }
[[nodiscard]] constexpr bool hasThreadSanitizer() noexcept { return ENGINE_HAS_TSAN != 0; }
[[nodiscard]] constexpr bool assertsEnabled() noexcept { return ENGINE_ASSERTS_ENABLED != 0; }

[[nodiscard]] constexpr bool isOptimizedBuild() noexcept {
#if defined(NDEBUG)
    return true;
#else
    return false;
#endif
}

}  // namespace engine
