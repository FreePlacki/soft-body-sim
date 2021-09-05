/**
 * Handles onClick and button rendering
*/

#pragma once

#include <string>
#include <functional>
#include <iostream>
#include "vector2.h"


class Button {
public:
    Button(int x, int y, int width, int height, const std::string &text, sf::Color color=sf::Color::Blue);

    void draw(sf::RenderWindow &win);
    void setOnClick(const std::function<void()> &f);
    void onClick(const sf::Vector2i &mouse_pos) const;

public:
    Vector2 pos;
    int width, height;
    std::string text;

private:
    std::function<void()> on_click_fun;
    sf::Color color;
    sf::Font font;

private:
    bool isClicked(const sf::Vector2i &mouse_pos) const;
};