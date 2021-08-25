/**
 * Handles particle update and draw.
 * Contains particle's properties.
 * @file particle.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "../math/vector2.h"
#include <memory>


class Particle {
public:
    // radius
    const int r;
    // mass
    const double m;
    // integer color format
    const uint32_t color;
    
    // position
    Vector2 pos = Vector2(0, 0);
    // velocity
    Vector2 vel = Vector2(0, 0);

    // particles that are connected by a spring force (particle, x_0, k)
    std::vector<std::tuple<std::shared_ptr<Particle>, double, double>> connected;

    /**
     * Class constructor.
     * @param r radius
     * @param x x position of the center
     * @param y y position of the center
     * @param vx x component of the velocity
     * @param vy y component of the velocity
     * @param m mass
     * @param color color in uint32_t format
    */
    Particle(int r, double x, double y, double vx=0.0, double vy=0.0, double m=10.0, uint32_t color=sf::Color::Red.toInteger());
    
    /**
     * Applies forces and updates position and velocity.
     * @param fps current fps
    */
    void update(double fps);

    /**
     * Draws a particle (circle) to the window.
     * @param win window to draw on
    */
    void draw(sf::RenderWindow &win) const;

    /**
     * Adds a particle to the connected list.
     * Particles connected interact by a spring force.
     * @param p particle to connect to
    */
    void connect(std::shared_ptr<Particle> p, double x_0, double k);

private:
    /**
     * Calculates acceleration given current position
     * @return Vector2 acceleration
    */
    Vector2 calcAcceleration() const;
};
