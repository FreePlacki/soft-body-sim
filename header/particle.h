#pragma once

#include "vector2.h"
#include "constants.h"


class Particle {
public:
    int r;
    float m;
    int color;

    Vector2 pos = Vector2(0, 0);
    Vector2 vel = Vector2(0, 0);

    Particle(int r, float x, float y, float vx, float vy, float m=10.0, int color=1);
    void update(float dt);
};
