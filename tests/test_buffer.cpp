#include <type_traits>
#include <utility>

#include <doctest/doctest.h>

#include "engine/core/Buffer.h"

using engine::Buffer;

TEST_CASE("Buffer: construct") {
    Buffer b(5);
    CHECK(b.size() == 5);
}

TEST_CASE("Buffer: copy leaves the source intact") {
    Buffer a(3);
    Buffer b = a;
    CHECK(a.size() == 3);
    CHECK(b.size() == 3);
}

TEST_CASE("Buffer: move empties the source") {
    Buffer a(3);
    Buffer b = std::move(a);
    CHECK(b.size() == 3);
    CHECK(a.size() == 0);  // moved-from but still valid
}

TEST_CASE("Buffer: self-assignment keeps the data") {
    Buffer a(5);
    Buffer& alias = a;  // avoids the compiler's self-assign warning
    a = alias;
    CHECK(a.size() == 5);
}

TEST_CASE("Buffer: copy-assign into a larger buffer") {
    Buffer big(10), small(2);
    big = small;
    CHECK(big.size() == 2);
    CHECK(small.size() == 2);
}

TEST_CASE("Buffer: move-assign from a temporary") {
    Buffer b(2);
    b = Buffer(9);
    CHECK(b.size() == 9);
}

TEST_CASE("Buffer: move-assign from an lvalue via std::move") {
    Buffer a(4), b(1);
    b = std::move(a);
    CHECK(b.size() == 4);
    CHECK(a.size() == 0);
}

TEST_CASE("Buffer: swap exchanges contents") {
    Buffer a(3), b(7);
    a.swap(b);
    CHECK(a.size() == 7);
    CHECK(b.size() == 3);
}

TEST_CASE("Buffer: empty buffers are fine") {
    Buffer e(0);
    Buffer copy = e;
    Buffer moved = std::move(e);
    CHECK(copy.size() == 0);
    CHECK(moved.size() == 0);
}

TEST_CASE("Buffer: moves are noexcept") {
    CHECK(std::is_nothrow_move_constructible_v<Buffer>);
    CHECK(std::is_nothrow_move_assignable_v<Buffer>);
}
