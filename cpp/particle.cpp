#include "../header/particle.h"
#include <iostream>


Particle::Particle(int r, float x, float y, float vx, float vy, float m, int color) {
    this->r = r;
    this->pos = Vector2(x, y);
    this->vel = Vector2(vx, vy);
    this->m = m;
    this->color = color;
}

void Particle::update(float dt) {
    //Vector2 force = Vector2(0, this->m * g);
    Vector2 force = Vector2(0, 0);
    Vector2 acc = force / this->m;

    Vector2 dv = acc*1/FPS;
    Vector2 dp = this->vel*1/FPS;
    this->vel += dv;
    this->pos += dp;
    // std::cout << dt << "\n";
}