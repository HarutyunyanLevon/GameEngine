#include <chrono>
#include <thread>

#include <doctest/doctest.h>

#include "engine/core/Assert.h"
#include "engine/core/BuildInfo.h"
#include "engine/core/Timer.h"
#include "engine/core/Types.h"

TEST_CASE("fixed-width types have the expected sizes") {
    static_assert(sizeof(engine::u8) == 1);
    static_assert(sizeof(engine::u16) == 2);
    static_assert(sizeof(engine::u32) == 4);
    static_assert(sizeof(engine::u64) == 8);
    static_assert(sizeof(engine::f32) == 4);
    static_assert(sizeof(engine::f64) == 8);
    CHECK(engine::kCacheLineSize == 64);
}

TEST_CASE("Timer measures elapsed time and can be reset") {
    engine::Timer timer;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    const double first = timer.elapsedMillis();
    CHECK(first >= 4.0);

    timer.reset();
    CHECK(timer.elapsedMillis() < first);
}

TEST_CASE("ENGINE_ASSERT passes on a true condition") {
    ENGINE_ASSERT(1 + 1 == 2, "arithmetic still works");
    CHECK(true);
}

TEST_CASE("ENGINE_ASSERT does not evaluate its condition when disabled") {
    int evaluations = 0;
    ENGINE_ASSERT(++evaluations > 0, "side effect probe");
    CHECK(evaluations == (engine::assertsEnabled() ? 1 : 0));
}

TEST_CASE("BuildInfo reports a compiler") {
    CHECK(engine::compilerName()[0] != '\0');
}
