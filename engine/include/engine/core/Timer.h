#pragma once

#include <chrono>

namespace engine {

class Timer {
public:
    using Clock = std::chrono::steady_clock;

    Timer() noexcept : start_(Clock::now()) {}

    void reset() noexcept { start_ = Clock::now(); }

    [[nodiscard]] double elapsedSeconds() const noexcept {
        return std::chrono::duration<double>(Clock::now() - start_).count();
    }

    [[nodiscard]] double elapsedMillis() const noexcept { return elapsedSeconds() * 1000.0; }

private:
    Clock::time_point start_;
};

}  // namespace engine
