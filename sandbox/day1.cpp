#include <cstdio>
#include <utility>
#include <vector>

#include "engine/core/Buffer.h"

using engine::Buffer;

void take(Buffer&)       { std::printf("    take(Buffer&)\n"); }
void take(const Buffer&) { std::printf("    take(const Buffer&)\n"); }
void take(Buffer&&)      { std::printf("    take(Buffer&&)\n"); }

Buffer makeTemp()  { return Buffer(3); }
Buffer makeNamed() { Buffer b(3); return b; }
Buffer makeMoved() { Buffer b(3); return std::move(b); }

#define STEP(label) std::printf("\n[%s]\n", label)

int main() {
    Buffer::trace = true;  // print every constructor, assignment and destructor

    STEP("1 copy from lvalue"); // ctor a, COPY ctor
    Buffer a(3);
    Buffer b = a;

    STEP("2 move from std::move(lvalue)"); // MOVE ctor
    Buffer c = std::move(a);
    std::printf("    a.size() after move = %zu\n", a.size()); // 0

    STEP("3 std::move on a const object"); // ctor k, COPY ctor 
    const Buffer k(3);
    Buffer d = std::move(k);

    STEP("4 overloads: lvalue, const lvalue, std::move, prvalue"); // take(Buffer&), take(const Buffer&), take(Buffer&&), ctor , take(Buffer&&), dtor
    take(b);
    take(k);
    take(std::move(b));
    take(Buffer(1));

    STEP("5 return a prvalue"); // ctor
    Buffer e = makeTemp();

    STEP("6 return a named local"); // ctor
    Buffer f = makeNamed();

    STEP("7 return std::move(local)"); // ctor, MOVE ctor, dtor
    Buffer g = makeMoved();

    STEP("8 vector push_back"); // ctor, Move ctor, dtor, copy ctor
    std::vector<Buffer> v;
    v.reserve(4);
    v.push_back(Buffer(1));
    v.push_back(c);

    STEP("end of main");
}
