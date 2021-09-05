/**
 * Holds shape parameters and handles shape draw.
*/

#pragma once

#include "vector2.h"
#include <SFML/Graphics.hpp>
#include <array>


class Shape {
public:
    Shape(int x, int y, const std::vector<sf::Vector2f> &points, uint32_t outline_color=sf::Color::White.toInteger(), uint32_t background_color=sf::Color::Black.toInteger());

    static std::vector<sf::Vector2f> makeRect(int width, int height);    

    void draw(sf::RenderWindow &win) const;

public:
    Vector2 pos;

    std::vector<sf::Vector2f> points;
    // shape's farthest points
    std::map<std::string, int> bondries = {
        {"top", -1},
        {"bottom", -1},
        {"left", -1},
        {"right", -1}
    };

    // uint32_t type to convert to sf::Color
    uint32_t outline_color;
    uint32_t background_color;

private:
    void setBondries(const std::vector<sf::Vector2f> &points);
};