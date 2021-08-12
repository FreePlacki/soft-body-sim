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
    // relative points coordinates for constructing the convex
    static constexpr int MAX_POINT_COUNT = 20;
    int point_count;
    sf::Vector2f points[MAX_POINT_COUNT];
    // shape's farthest points
    std::map<std::string, int> bondries = {
        {"top", -1},
        {"bottom", -1},
        {"left", -1},
        {"right", -1}
    };
    // TODO implement rotation
    // uint32_t format to convert to sf::Color
    uint32_t outline_color;
    uint32_t background_color;

    /**
     * Class constructor. Calculates points given width, height, rotation
     * @param x x position
     * @param y y position
     * @param point_count number of points to create the shape
     * @param points array of point coordinates in sf::Vector2f format
     * @param outline_color color of the outline in uint32_t format
     * @param background_color color of the background in uint32_t format
    */
    Shape(int x, int y, int point_count, sf::Vector2f points[MAX_POINT_COUNT], uint32_t outline_color=sf::Color::White.toInteger(), uint32_t background_color=sf::Color::Black.toInteger());

    /**
     * Draws the shape to the window.
     * @param win window to draw on
    */
    void draw(sf::RenderWindow &win);
};