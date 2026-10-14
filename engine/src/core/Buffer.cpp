
#include "engine/core/Buffer.h"
#include <cstdio>
#include <utility>

namespace engine {

Buffer::Buffer(std::size_t n)
    : size_(n)
    , data_(new int[n]{})
{
    std::printf("ctor n\n");
}

Buffer::~Buffer() {
    std::printf("dtor\n");
    delete[] data_;
}

Buffer::Buffer(const Buffer& other)
    : size_(other.size_)
    , data_(new int[other.size_])
{
    std::printf("COPY ctor\n");

    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

Buffer::Buffer(Buffer&& other) noexcept
    : size_(other.size_)
    , data_(other.data_)
{
    std::printf("MOVE ctor\n");

    other.size_ = 0;
    other.data_ = nullptr;
}

Buffer& Buffer::operator=(const Buffer& other) {
    std::printf("COPY assign\n");

    if (this == &other)
        return *this;

    int* new_data = new int[other.size_];

    for (std::size_t i = 0; i < other.size_; ++i) {
        new_data[i] = other.data_[i];
    }

    delete[] data_;

    data_ = new_data;
    size_ = other.size_;

    return *this;
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
    std::printf("MOVE assign\n");

    if (this == &other)
        return *this;

    delete[] data_;

    size_ = other.size_;
    data_ = other.data_;

    other.size_ = 0;
    other.data_ = nullptr;

    return *this;
}

std::size_t Buffer::size() const {
    return size_;
}

}
