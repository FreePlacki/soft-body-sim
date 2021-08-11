/**
 * Handles particle update and draw.
 * Contains particle's properties.
 * @file particle.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "vector2.h"
#include "constants.h"


class Particle {
public:
    // radius
    int r;
    // mass
    double m;
    // 1 - red
    int color;
    
    // position
    Vector2 pos = Vector2(0, 0);
    // velocity
    Vector2 vel = Vector2(0, 0);

    /**
     * Class constructor.
     * @param r radius
     * @param x x position of the center
     * @param y y position of the center
     * @param vx x component of the velocity
     * @param vy y component of the velocity
     * @param m mass
     * @param color color
    */
    Particle(int r, double x, double y, double vx, double vy, double m=10.0, uint32_t color=sf::Color::Red.toInteger());
    
    /**
     * Applies forces and updates position and velocity.
    */
    void update();

    /**
     * Draws a particle (circle) to the window.
     * @param win window to draw on
    */
    void draw(sf::RenderWindow &win);
};
