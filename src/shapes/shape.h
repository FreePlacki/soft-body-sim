/**
 * Holds shape parameters and handles shape draw.
 * @file shape.h
*/

#pragma once

#include "../math/vector2.h"
#include <SFML/Graphics.hpp>
#include <array>


class Shape {
public:
    // position
    Vector2 pos = Vector2(0, 0);
    int width, height;
    // relative points coordinates for constructing the convex
    int point_count;
    std::vector<sf::Vector2f> points;
    // shape's farthest points
    std::map<std::string, int> bondries = {
        {"top", -1},
        {"bottom", -1},
        {"left", -1},
        {"right", -1}
    };

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
    Shape(int x, int y, int point_count, const std::vector<sf::Vector2f> &points, uint32_t outline_color=sf::Color::White.toInteger(), uint32_t background_color=sf::Color::Black.toInteger());

    /**
     * Returns points needed to make a rectangle
     * @param x x position
     * @param y y position
     * @return sf::Vector2f array of point coordinates
    */
    static std::vector<sf::Vector2f> makeRect(int width, int height);    

    /**
     * Draws the shape to the window.
     * @param win window to draw on
    */
    void draw(sf::RenderWindow &win) const;

private:
    /**
     * Helper function the set the shape's bondries.
     * @param points an array of sf::Vector2f point coordinates
     * @param point_count number of points
    */
    void setBondries(const std::vector<sf::Vector2f> &points, int point_count);
};