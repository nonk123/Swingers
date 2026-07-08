#include <raylib.h>

#include "clock.hpp"

Clock::Clock(double interval) : interval(interval) {}

Clock::operator bool() {
    const double now = GetTime();

    if (last_tick == 0.0 || now - last_tick >= interval) {
        last_tick = now;
        return true;
    } else {
        return false;
    }
}
