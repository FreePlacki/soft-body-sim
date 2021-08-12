/**
 * Implements methods from the Shape class.
 * @file shape.cpp
*/

#include "../header/shape.h"
#include <iostream>


// constructor
Shape::Shape(int x, int y, int point_count, sf::Vector2f points[MAX_POINT_COUNT], uint32_t outline_color, uint32_t background_color) {
    this->pos = Vector2(x, y);
    this->point_count = point_count;
    this->outline_color = outline_color;
    this->background_color = background_color;

    for (int i = 0; i < point_count; i++) {
        this->points[i] = points[i];

        // setting bondries
        int x = points[i].x + this->pos.x;
        int y = points[i].y + this->pos.y;
        if (this->bondries["right"] == -1
        || x > this->bondries["right"])
            this->bondries["right"] = x;
        if (this->bondries["left"] == -1
        || x < this->bondries["left"])
            this->bondries["left"] = x;
        if (this->bondries["top"] == -1
        || y < this->bondries["top"])
            this->bondries["top"] = y;
        if (this->bondries["bottom"] == -1
        || y > this->bondries["bottom"])
            this->bondries["bottom"] = y;
    }
    // std::cout << bondries["top"] << " : " << bondries["right"] << " : " << bondries["bottom"] << " : " << bondries["left"] << "\n";
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