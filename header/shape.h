/**
 * Holds shape parameters and handles shape draw.
 * @file shape.h
*/

#pragma once

#include "vector2.h"
#include <SFML/Graphics.hpp>


class Shape {
public:
    // position
    Vector2 pos = Vector2(0, 0);
    int width, height;
    // in degrees
    double rotation;
    // uint32_t format to convert to sf::Color
    uint32_t outline_color;
    uint32_t background_color;

    /**
     * Class constructor
     * @param x x position
     * @param y y position
     * @param width shape's width in pixels
     * @param height shape's height in pixels
     * @param rotation shape's rotation in degrees
     * @param outline_color color of the outline in uint32_t format
     * @param background_color color of the background in uint32_t format
    */
    Shape(int x, int y, int width, int height, double rotation=0, uint32_t outline_color=sf::Color::White.toInteger(), uint32_t background_color=sf::Color::Black.toInteger());

    /**
     * Draws the shape to the window.
     * @param win window to draw on
    */
    void draw(sf::RenderWindow &win);
};