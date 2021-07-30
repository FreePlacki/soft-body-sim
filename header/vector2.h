#pragma once

#include <cmath>

class Vector2 {
public:
    float x, y;

    Vector2(float x, float y);
    //Vector2() = default;

    float length();
    float length_sq();
    float dist(Vector2 &v);
    float dist_sq(Vector2 &v);
    void limit(float max);

    Vector2 operator+(Vector2 &v);
    Vector2 operator-(Vector2 &v);
    float operator*(Vector2 &v);
    Vector2 operator*(float a);
    Vector2 operator/(float a);
    void operator+=(Vector2 &v);
    void operator-=(Vector2 &v);
    void operator*=(float a);
};
