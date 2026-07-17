#pragma once

#include <S_fixed.h>

#include <raylib.h>

struct Vec3 {
    Fixed x, y, z;

    Vec3() : Vec3(Fx0, Fx0, Fx0) {}
    Vec3(Fixed x, Fixed y, Fixed z) : x(x), y(y), z(z) {}
    Vec3(double x, double y, double z) : Vec3(Double2Fx(x), Double2Fx(y), Double2Fx(z)) {}

    Vec3 operator+(const Vec3& other) const {
        return Vec3(Fadd(x, other.x), Fadd(y, other.y), Fadd(z, other.z));
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(Fsub(x, other.x), Fsub(y, other.y), Fsub(z, other.z));
    }

    Vec3 operator+=(const Vec3& other) {
        x = Fadd(x, other.x), y = Fadd(y, other.y), z = Fadd(z, other.z);
        return *this;
    }

    Vec3 operator*=(const Fixed& s) {
        x = Fmul(x, s), y = Fmul(y, s), z = Fmul(z, s);
        return *this;
    }

    operator Vector3() const {
        return Vector3{Fx2Float(x), Fx2Float(y), Fx2Float(z)};
    }
};
