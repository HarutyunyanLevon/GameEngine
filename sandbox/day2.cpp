#include <cstdio>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "engine/core/Buffer.h"

// Wraps a Buffer and counts copies/moves. Nx decides whether the move ctor is noexcept.
template <bool Nx>
struct Tracked {
    static inline int copies = 0, moves = 0;
    static void reset() { copies = moves = 0; }
    engine::Buffer b{4};
    Tracked() = default;
    Tracked(const Tracked& o) : b(o.b) { ++copies; }
    Tracked(Tracked&& o) noexcept(Nx) : b(std::move(o.b)) { ++moves; }
    Tracked& operator=(const Tracked& o) {++copies; b=o.b; return *this;}
    Tracked& operator=(Tracked&& o) noexcept(Nx) { ++moves; b = std::move(o.b); return *this; }
};

struct SpriteZero { Tracked<true> t; std::string name = "s"; };
struct SpriteDtor {
    Tracked<true> t;
    std::string name = "s";
    SpriteDtor() = default;
    SpriteDtor(SpriteDtor&& o) noexcept : t(std::move(o.t)), name(std::move(o.name)) {}
    SpriteDtor(const SpriteDtor& o) : t(o.t), name(o.name) {}
    SpriteDtor& operator=(SpriteDtor&& o) noexcept {
        t = std::move(o.t);
        name = std::move(o.name);
        return *this;
    }
    SpriteDtor& operator=(const SpriteDtor& o) {
        t = o.t;
        name = o.name;
        
        return *this;
    }
    
    ~SpriteDtor() noexcept {}
};

template <class T>
void grow(const char* label, int n) {
    T::reset();
    std::vector<T> v;
    for (int i = 0; i < n; ++i) v.emplace_back();
    std::printf("%-26s n=%-3d copies=%-3d moves=%d\n", label, n, T::copies, T::moves);
}

int main() {
    grow<Tracked<true>>("Tracked noexcept", 8);
    grow<Tracked<false>>("Tracked may-throw", 8);
    grow<Tracked<true>>("Tracked noexcept", 100);
    grow<Tracked<false>>("Tracked may-throw", 100);
    for (int pass = 0; pass < 2; ++pass) {
        Tracked<true>::reset();
        if (pass == 0) { std::vector<SpriteZero> v; for (int i = 0; i < 8; ++i) v.emplace_back(); }
        else           { std::vector<SpriteDtor> v; for (int i = 0; i < 8; ++i) v.emplace_back(); }
        std::printf("%s  nothrow-movable=%d  Buffer copies=%d moves=%d\n",
                    pass == 0 ? "SpriteZero" : "SpriteDtor",
                    pass == 0 ? (int)std::is_nothrow_move_constructible_v<SpriteZero>
                              : (int)std::is_nothrow_move_constructible_v<SpriteDtor>,
                    Tracked<true>::copies, Tracked<true>::moves);
    }
}