/**
 * Handles window creation and holds window's parameters.
 * @file window.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "particle.h"
#include <string>


class Window {
private:
    sf::RenderWindow render_window;
    const std::string TITLE = "Soft Body Sim";
    // default settings changed at constructor
    std::map<std::string, int> settings {
        {"WIN_WIDTH", 800},
        {"WIN_HEIGHT", 800},
        {"MAX_FPS", 60}
    };

public:
    /**
     * Class constructor.
     * @param settings map<string, int> of program settings
    */
    Window(const std::map<std::string, int> &settings);

    /**
     * Getter for the window's sf::RenderWindow object.
     * @return sf::RenderWindow object
    */
    sf::RenderWindow& getWin();

    /**
     * Getter for window's dimensions.
     * @return std::pair<int, int> with window's width and height
    */
    const std::pair<int, int> getSize() const;

    /**
     * Getter for window's title.
     * @return std::string window's title
    */
    const std::string& getTitle() const;

    /**
     * Getter for window's max fps.
     * @return int max window's fps
    */
    int getFps() const;

    const std::map<std::string, int>& getSettings() const;
};