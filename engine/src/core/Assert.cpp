#include "engine/core/Assert.h"

#include <cstdio>
#include <cstdlib>

namespace engine::detail {

void assertFail(const char* expr, const char* file, int line, const char* msg) noexcept {
    std::fprintf(stderr, "ENGINE_ASSERT failed: %s\n  %s\n  at %s:%d\n", expr, msg, file, line);
    std::fflush(stderr);
    std::abort();
}

}  // namespace engine::detail
