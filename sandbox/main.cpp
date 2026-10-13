#include <cstdio>
#include <thread>

#include "engine/core/BuildInfo.h"
#include "engine/core/Timer.h"
#include "engine/core/Types.h"

int main() {
    using namespace engine;

    Timer timer;

    std::printf("mini-engine sandbox\n");
    std::printf("  compiler        : %s\n", compilerName());
    std::printf("  C++ standard    : %ld\n", static_cast<long>(__cplusplus));
    std::printf("  optimized build : %s\n", isOptimizedBuild() ? "yes" : "no");
    std::printf("  asserts enabled : %s\n", assertsEnabled() ? "yes" : "no");
    std::printf("  ASan / TSan     : %s / %s\n", hasAddressSanitizer() ? "on" : "off",
                hasThreadSanitizer() ? "on" : "off");
    std::printf("  cache line      : %zu bytes\n", kCacheLineSize);
    std::printf("  hw threads      : %u\n", std::thread::hardware_concurrency());
    std::printf("  startup         : %.3f ms\n", timer.elapsedMillis());
    return 0;
}
