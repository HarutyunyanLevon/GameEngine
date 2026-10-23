#include "engine/core/Buffer.h"

#include <cstdio>
#include <utility>

namespace engine {

namespace {
void log(const char* what) {
    if (Buffer::trace) std::printf("    %s\n", what);
}
}  // namespace

Buffer::Buffer(std::size_t n)
    : size_(n)
    , data_(new int[n]{})
{
    log("ctor");
}

Buffer::~Buffer() noexcept {
    log("dtor");
    delete[] data_;
}

Buffer::Buffer(const Buffer& other)
    : size_(other.size_)
    , data_(new int[other.size_])
{
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    log("COPY ctor");
}

Buffer::Buffer(Buffer&& other) noexcept
    : size_(other.size_)
    , data_(other.data_)
{
    other.size_ = 0;
    other.data_ = nullptr;
    log("MOVE ctor");
}

Buffer& Buffer::operator=(Buffer other) noexcept {
    log("assign (by value, then swap)");
    swap(other);
    return *this;  // 'other' now holds our old data and frees it here
}

void Buffer::swap(Buffer& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

std::size_t Buffer::size() const noexcept {
    return size_;
}

}  // namespace engine
