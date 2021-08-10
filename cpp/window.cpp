/**
 * Implements methods from the Window class.
 * @file window.cpp
*/

#include "../header/window.h"


// constructor
Window::Window(int width, int height, std::string title, int FPS) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->fps = fps;

    this->render_window.create(sf::VideoMode(width, height), title);
    this->render_window.setFramerateLimit(FPS);
}

// RenderWindow getter
sf::RenderWindow& Window::getWin() {
    return this->render_window;
}

// width and height getter
std::pair<int, int> Window::getSize() {
    return std::make_pair(this->width, this->height);
}

// title getter
std::string Window::getTitle() {
    return this->title;
}

// max fps getter
int Window::getFps() {
    return this->fps;
}