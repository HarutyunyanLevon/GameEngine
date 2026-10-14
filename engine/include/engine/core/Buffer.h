#pragma once

#include <cstddef>

namespace engine {

class Buffer {
public:
    explicit Buffer(std::size_t n);
    ~Buffer();
    Buffer(const Buffer&);
    Buffer(Buffer&&) noexcept;
    Buffer& operator=(const Buffer&);
    Buffer& operator=(Buffer&&) noexcept;
    std::size_t size() const;
private:
    std::size_t size_;
    int* data_;
};
}  // namespace engine
