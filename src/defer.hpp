#pragma once

#include <functional>

#define defer_2(line, fn) Defer defer_##line(fn)
#define defer_1(line, fn) defer_2(line, fn)
#define defer(fn) defer_1(__LINE__, fn)

struct Defer {
    const std::function<void()> functor;
    Defer(const std::function<void()>&);
    ~Defer();
};
