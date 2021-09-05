#include "button.h"

Button::Button(int x, int y, int width, int height, const std::string &text, sf::Color color)
    :width(width), height(height), text(text), color(color) {
    this->pos = Vector2(x, y);
    if (!font.loadFromFile("res/fonts/Roboto-Regular.ttf"))
        std::cout << "Error loading font: res/fonts/Roboto-Regular.ttf\n";
}

void Button::setOnClick(const std::function<void()> &f) {
    this->on_click_fun = f;
}

void Button::onClick(const sf::Vector2i &mouse_pos) const {
    if (isClicked(mouse_pos))
        on_click_fun();
}

bool Button::isClicked(const sf::Vector2i &mouse_pos) const {
    return mouse_pos.x >= this->pos.x
        && mouse_pos.x <= this->pos.x+this->width
        && mouse_pos.y >= this->pos.y
        && mouse_pos.y <= this->pos.y+this->height;
}

void Button::draw(sf::RenderWindow &win) {
    sf::RectangleShape rect(sf::Vector2f(this->width, this->height));
    rect.setPosition(sf::Vector2f(pos.x, pos.y));
    rect.setFillColor(this->color);

    sf::Text t;
    t.setFont(this->font);
    t.setString(this->text);
    t.setCharacterSize(16);

    sf::FloatRect bounds = t.getGlobalBounds();
    float x_pos = this->pos.x + (this->width-bounds.width)/2;
    float y_pos = this->pos.y + (this->height-bounds.height)/2;
    t.setPosition(sf::Vector2f(x_pos, y_pos));
    
    
    win.draw(rect);
    win.draw(t);
}