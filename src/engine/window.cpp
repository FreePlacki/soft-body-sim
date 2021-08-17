/**
 * Implements methods from the Window class.
 * @file window.cpp
*/

#include "window.h"


// constructor
Window::Window(const std::map<std::string, int> &settings) {
    this->settings["WIN_WIDTH"] = settings.at("WIN_WIDTH");
    this->settings["WIN_HEIGHT"] = settings.at("WIN_HEIGHT");
    this->settings["MAX_FPS"] = settings.at("MAX_FPS");

    this->render_window.create(sf::VideoMode(settings.at("WIN_WIDTH"), settings.at("WIN_HEIGHT")), TITLE);
    this->render_window.setFramerateLimit(settings.at("MAX_FPS"));
}

// RenderWindow getter
sf::RenderWindow& Window::getWin() {
    return this->render_window;
}

// width and height getter
const std::pair<int, int> Window::getSize() const {
    return std::make_pair(settings.at("WIN_WIDTH"), settings.at("WIN_HEIGHT"));
}

// title getter
const std::string& Window::getTitle() const {
    return this->TITLE;
}

// max fps getter
int Window::getFps() const {
    return settings.at("MAX_FPS");
}

const std::map<std::string, int>& Window::getSettings() const {
    return this->settings;
}