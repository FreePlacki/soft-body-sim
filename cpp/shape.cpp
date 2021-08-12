/**
 * Implements methods from the Shape class.
 * @file shape.cpp
*/

#include "../header/shape.h"


// constructor
Shape::Shape(int x, int y, int point_count, sf::Vector2f points[MAX_POINT_COUNT], uint32_t outline_color, uint32_t background_color) {
    this->pos = Vector2(x, y);
    this->point_count = point_count;
    this->outline_color = outline_color;
    this->background_color = background_color;

    for (int i = 0; i < point_count; i++) {
        this->points[i] = points[i];
    }
}

// draws the shape to the window
void Shape::draw(sf::RenderWindow &win) {
    sf::ConvexShape polygon(this->point_count);
    for (int i = 0; i < this->point_count; i++) {
        polygon.setPoint(i, this->points[i]);
    }

    polygon.setOutlineColor(sf::Color(this->outline_color));
    polygon.setFillColor(sf::Color(this->background_color));
    polygon.setOutlineThickness(5);
    polygon.setPosition(this->pos.x, this->pos.y);

    win.draw(polygon);
}