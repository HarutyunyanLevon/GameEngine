#pragma once

#include <cstddef>
#include <type_traits>

namespace engine {

class Buffer {
public:
    // Learning aid: set to true to print every special-member call (see sandbox/day1.cpp).
    static inline bool trace = false;

    explicit Buffer(std::size_t n);
    ~Buffer() noexcept;
    Buffer(const Buffer&);
    Buffer(Buffer&&) noexcept;
    // Copy-and-swap: takes its argument by value, so one operator covers copy and move assignment.
    Buffer& operator=(Buffer other) noexcept;
    void swap(Buffer& other) noexcept;
    std::size_t size() const noexcept;
private:
    std::size_t size_;
    int* data_;
};

}  // namespace engine

static_assert(std::is_nothrow_move_constructible_v<engine::Buffer>);
static_assert(std::is_nothrow_move_assignable_v<engine::Buffer>);
