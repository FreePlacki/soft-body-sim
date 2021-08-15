/**
 * Handles window creation and holds window's parameters.
 * @file window.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "particle.h"


class Window {
private:
    sf::RenderWindow render_window;
    int width, height;
    std::string title;
    int fps;

public:
    /**
     * Class constructor.
     * @param width window's width in pixels
     * @param height window's height in pixels
     * @param title window's title
     * @param fps max frames per second
    */
    Window(int width, int height, std::string title, int fps);

    /**
     * Getter for the window's sf::RenderWindow object.
     * @return sf::RenderWindow object
    */
    sf::RenderWindow& getWin();

    /**
     * Getter for window's dimensions.
     * @return std::pair<int, int> with window's width and height
    */
    std::pair<int, int> getSize() const;

    /**
     * Getter for window's title.
     * @return std::string window's title
    */
    std::string getTitle() const;

    /**
     * Getter for window's max fps.
     * @return int max window's fps
    */
    int getFps() const;
};