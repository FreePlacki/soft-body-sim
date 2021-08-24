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

    // particles that are connected by a spring force
    std::vector<std::shared_ptr<Particle>> connected;

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
    void update(int fps);

    /**
     * Draws a particle (circle) to the window.
     * @param win window to draw on
    */
    void draw(sf::RenderWindow &win) const;

    /**
     * Adds a particle to the connectes list.
     * Particles connected interact by a spring force.
     * @param p particle to connect to
    */
    void connect(std::shared_ptr<Particle> p);
};
