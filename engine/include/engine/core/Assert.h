#pragma once

namespace engine::detail {

[[noreturn]] void assertFail(const char* expr, const char* file, int line, const char* msg) noexcept;

}  // namespace engine::detail

#if !defined(NDEBUG) || defined(ENGINE_FORCE_ASSERTS)
#define ENGINE_ASSERTS_ENABLED 1
#define ENGINE_ASSERT(cond, msg)                                                  \
    do {                                                                          \
        if (!(cond)) [[unlikely]] {                                               \
            ::engine::detail::assertFail(#cond, __FILE__, __LINE__, (msg));       \
        }                                                                         \
    } while (false)
#else
#define ENGINE_ASSERTS_ENABLED 0
#define ENGINE_ASSERT(cond, msg) \
    do {                         \
        (void)sizeof(cond);      \
    } while (false)
#endif
