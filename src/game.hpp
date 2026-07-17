#pragma once

#include <NutBlast.h>

#include "vec3.hpp"

constexpr const int TICKRATE = 60;

void init(), restart(), update(), draw();

void draw_cube(Vec3, Vec3, Color);

struct Platform {
    Vec3 pos, dim;

    Platform(Vec3 pos, Vec3 dim) : pos(pos), dim(dim) {}

    void draw() const;
};

struct Player {
    NutBlast_ID id;
    Vec3 pos;

    Player(NutBlast_ID id) : id(id) {}

    void draw() const;
};
