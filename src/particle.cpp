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
void Particle::update(double fps) {

    Vector2 acc = calcAcceleration();

    // TODO temp time slowdown
    // fps /= 3;
    double dt = 1/fps;

    // v(t + 1/2dt)
    this->vel += acc/2 * dt;
    // x(t + dt)
    this->pos += this->vel*1/fps;
    // a(t + dt)
    Vector2 acc2 = calcAcceleration();
    // v(t + dt)
    this->vel += acc2/2 * dt;
}

// acceleration at current x value
Vector2 Particle::calcAcceleration() const {
    constexpr double g = 100.0;
    constexpr double damp = 50.0;

    Vector2 force = Vector2(0, this->m * g);
    for (auto el : this->connected) {
        auto p = std::get<0>(el);
        double x_0 = std::get<1>(el);
        double k = std::get<2>(el);

        Vector2 x_diff = p->pos - this->pos;
        Vector2 v_diff = p->vel - this->vel;
        double len = x_diff.length();
        // TODO spring force not working properly+ x_diff/len*v_diff*damp
        // force += diff/len * ((len - x_0) * k);
        Vector2 s_force = x_diff/len*((len-x_0)*k + x_diff/len*v_diff*damp);
        force += s_force;

        // update second particle
        // (*p).vel += s_force/(*p).m / fps;
        // (*p).pos += (*p).vel / fps;
    }

    Vector2 acc = force / this->m;

    return acc;
}

// draws circle to the window
void Particle::draw(sf::RenderWindow &win) const {
    sf::CircleShape circ(this->r);
    circ.setFillColor(sf::Color(this->color));
    circ.setOrigin(this->r, this->r);
    circ.setPosition(this->pos.x, this->pos.y);

    for (auto el : connected) {
        auto p = std::get<0>(el);
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(this->pos.x, this->pos.y), sf::Color::White),
            sf::Vertex(sf::Vector2f(p->pos.x, p->pos.y), sf::Color::White),
        };

        win.draw(line, 2, sf::Lines);
    }

    win.draw(circ);
}

// connects with another particle
void Particle::connect(std::shared_ptr<Particle> p, double x_0, double k) {
    std::shared_ptr<Particle> this_p(this);

    this_p->connected.push_back(std::make_tuple(p, x_0, k));
    // add this particle to the other's list also
    (*p).connected.push_back(std::make_tuple(this_p, x_0, k));
}