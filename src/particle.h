/**
 * Handles particle update and draw.
 * Contains particle's properties.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "vector2.h"
#include <memory>


class Particle {
public:
    Particle(int r, double x, double y, double vx=0.0, double vy=0.0, double m=10.0, uint32_t color=sf::Color::Red.toInteger());
    
    void update(double fps);
    void draw(sf::RenderWindow &win) const;

    // connects to a particle by a spring force
    void connect(std::shared_ptr<Particle> p, double x_0, double k);

public:
    const int r;
    const double m;
    const uint32_t color;
    
    Vector2 pos = Vector2(0, 0);
    Vector2 vel = Vector2(0, 0);

    // particles that are connected with it by a spring force (particle, x_0, k)
    std::vector<std::tuple<std::shared_ptr<Particle>, double, double>> connected;

private:
    // acceleration at current position
    Vector2 calcAcceleration() const;
};
