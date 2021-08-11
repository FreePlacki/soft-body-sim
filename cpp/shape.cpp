/**
 * Implements methods from the Shape class.
 * @file shape.cpp
*/

#include "../header/shape.h"


// constructor
Shape::Shape(int x, int y, int width, int height, uint32_t outline_color, uint32_t background_color) {
    this->pos = Vector2(x, y);
    this->width = width;
    this->height = height;
    this->outline_color = outline_color;
    this->background_color = background_color;
}

// draws the shape to the window
void Shape::draw(sf::RenderWindow &win) {
    sf::RectangleShape rect(sf::Vector2f(this->width, this->height));
    rect.setOutlineColor(sf::Color(this->outline_color));
    rect.setOutlineThickness(5);
    rect.setPosition(this->pos.x, this->pos.y);
    rect.setFillColor(sf::Color(this->background_color));
    win.draw(rect);
}