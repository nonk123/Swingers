#pragma once

struct Clock {
    double last_tick = 0.0;
    const double interval;

    Clock(double);
    explicit operator bool();
};
