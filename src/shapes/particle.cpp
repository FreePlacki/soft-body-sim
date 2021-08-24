/**
 * Implements methods from the Particle class.
 * @file particle.cpp
*/

#include "particle.h"
#include <iostream>


// constructor
Particle::Particle(int r, double x, double y, double vx, double vy, double m, uint32_t color):
    r(r), m(m), color(color) {
    this->pos = Vector2(x, y);
    this->vel = Vector2(vx, vy);
}

// applies force and updates pos and vel
void Particle::update(int fps) {
    constexpr double g = 100.0;
    constexpr double k = 30.0;
    constexpr double damp = 1.0;
    constexpr double x_0 = 100.0;

    Vector2 force = Vector2(0, this->m * g);
    for (auto p : this->connected) {
        Vector2 diff = p->pos - this->pos;
        double len = diff.length();
        // - this->vel.length() * damp is for damping
        force += diff/len * ((len - x_0) * k - this->vel.length() * damp);
    }

    // TODO fix damping
    // force -= this->vel/this->vel.length() * damp;

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

    for (auto p : connected) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(this->pos.x, this->pos.y), sf::Color::White),
            sf::Vertex(sf::Vector2f(p->pos.x, p->pos.y), sf::Color::White),
        };

        win.draw(line, 2, sf::Lines);
    }

    win.draw(circ);
}

// connects with another particle
void Particle::connect(std::shared_ptr<Particle> p) {
    std::shared_ptr<Particle> this_p(this);

    this_p->connected.push_back(p);
    // add this particle to the other's list also
    (*p).connected.push_back(this_p);
}