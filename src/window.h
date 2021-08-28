/**
 * Handles window creation and holds window's parameters.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "particle.h"
#include <string>


class Window {
private:
    sf::RenderWindow render_window;
    const std::string TITLE = "Soft Body Sim";
    // default settings, changed at constructor
    std::map<std::string, int> settings {
        {"WIN_WIDTH", 800},
        {"WIN_HEIGHT", 800},
        {"MAX_FPS", 60}
    };

public:
    Window(const std::map<std::string, int> &settings);

    sf::RenderWindow& getWin();
    // pair(width, height)
    const std::pair<int, int> getSize() const;
    const std::string& getTitle() const;
    // max set fps (not dynamically calculated)
    int getFps() const;
    const std::map<std::string, int>& getSettings() const;
};