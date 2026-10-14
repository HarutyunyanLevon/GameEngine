# mini-engine

A small C++20 engine core, built piece by piece as a learning project: allocators, an ECS, a job
system, and a simulation with measured before/after numbers.

## Quick start

Requirements: CMake 3.25+ and a C++20 compiler. Linux and macOS use Ninja with clang or gcc.
Windows uses Visual Studio 2022 (MSVC): see the Windows section below.

```sh
cmake --preset dev            # configure (Debug, asserts on)
cmake --build --preset dev
ctest --preset dev
./build/dev/sandbox/sandbox   # prints how this binary was built
```

## Presets

| Preset    | What it is                              | Use it for                              |
| --------- | --------------------------------------- | --------------------------------------- |
| `dev`     | Debug, asserts on                       | everyday development and debugging      |
| `asan`    | Debug + AddressSanitizer + UBSan        | lifetime bugs, UB, leaks (run often)    |
| `tsan`    | Debug + ThreadSanitizer                 | data races (from Day 15 on)             |
| `release` | RelWithDebInfo (`-O2 -g`), benchmarks on | every number you put in this README     |

Run tests under sanitizers the same way: `cmake --preset asan && cmake --build --preset asan && ctest --preset asan`.

Never record benchmark numbers from `dev`, `asan` or `tsan`. Use `release`, close other apps, and
plug the laptop in.

```sh
cmake --preset release
cmake --build --preset release
./build/release/bench/engine_bench
```

## Windows (MSVC)

The `win-*` presets use the Visual Studio 2022 generator, which finds MSVC and the Windows SDK by
itself, so they work from any terminal or IDE, no Developer Command Prompt needed.

| Preset        | What it is                                   | Use it for                             |
| ------------- | -------------------------------------------- | -------------------------------------- |
| `win-dev`     | Debug                                        | everyday development and debugging     |
| `win-asan`    | Debug + AddressSanitizer (experimental)      | lifetime bugs; no UBSan on MSVC        |
| `win-release` | RelWithDebInfo, benchmarks on                | every number you put in this README    |

```powershell
cmake --preset win-dev
cmake --build --preset win-dev
ctest --preset win-dev
.\build\win-dev\sandbox\Debug\sandbox.exe   # multi-config: binaries live in a Debug\ folder
```

The Ninja-based presets (`dev`, `asan`, `tsan`, `release`) also work on Windows, but only from an
"x64 Native Tools Command Prompt for VS 2022" (or after running `vcvars64.bat`), otherwise the
linker cannot find the Windows SDK (`LNK1104: cannot open file 'kernel32.lib'`).

`win-asan` needs the "C++ AddressSanitizer" component of the Visual Studio installer. If the tests
fail to start with a missing `clang_rt.asan_*.dll`, run `ctest` from a Developer prompt.
MSVC may not apply NRVO in Debug builds, so copy-elision experiments can differ from GCC and Clang;
compare with `win-release`.

## Layout

```
engine/    static library (sources in engine/src/, headers in engine/include/engine/)
sandbox/   executable for trying things out
tests/     doctest unit tests; every test_*.cpp is picked up automatically
bench/     Google Benchmark; every bench_*.cpp is picked up automatically
cmake/     shared compiler and sanitizer options
```

Adding an exercise is one file (a new .cpp under `engine/src/` is compiled automatically too): drop `tests/test_buffer.cpp` or `bench/bench_aos_vs_soa.cpp` in
place and rebuild. Headers go under `engine/include/engine/<area>/`.

Tip for editors: `ln -s build/dev/compile_commands.json .` gives clangd and most IDEs the right flags.

## Roadmap

- [ ] Week 1: `Buffer` (move semantics), `unique_ptr`, pool allocator, arena allocator, AoS vs SoA benchmark
- [ ] Week 2: ECS with SoA storage, OOP baseline, profiling, open-addressing hash map
- [ ] Week 3: job system, parallel ECS update, fixed-timestep loop, uniform grid
- [ ] Week 4: math library (`Vec3`, `Mat4`, `Quat`)

## Benchmark results

Record every experiment here: what changed, the numbers before and after, and what you learned.
Machine: _fill in CPU, OS, compiler, flags_.

| Experiment | Before | After | Notes |
| ---------- | ------ | ----- | ----- |
|            |        |       |       |
