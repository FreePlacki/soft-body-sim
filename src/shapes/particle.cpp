/**
 * Implements methods from the Particle class.
 * @file particle.cpp
*/

#include "particle.h"
#include <iostream>


// constructor
Particle::Particle(int r, double x, double y, double vx, double vy, double m, uint32_t color) {
    this->r = r;
    this->pos = Vector2(x, y);
    this->vel = Vector2(vx, vy);
    this->m = m;
    this->color = color;
}

// applies force and updates pos and vel
void Particle::update(int fps) {
    const int g = 100;

    Vector2 force = Vector2(0, this->m * g);
    Vector2 acc = force / this->m;

    Vector2 dv = acc*1/fps;
    Vector2 dp = this->vel*1/fps;
    this->vel += dv;
    this->pos += dp;
    // std::cout << dt << "\n";
}

// draws circle to the window
void Particle::draw(sf::RenderWindow &win) const {
    sf::CircleShape circ(this->r);
    circ.setFillColor(sf::Color(this->color));
    circ.setOrigin(this->r, this->r);
    circ.setPosition(this->pos.x, this->pos.y);

    // std::cout << this->color << "\n";
    // std::cout << sf::Color(sf::Color::Red.toInteger()) << "\n";

    win.draw(circ);
}

// TODO fix this
// void Particle::connect(std::shared_ptr<Particle> p) const {
//     this->connected.push_back(p);
// }