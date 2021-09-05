#include "uiManager.h"

UIManager::UIManager() {
    initUI();
}

void UIManager::draw(sf::RenderWindow &win) {
    for (Button &b : buttons)
        b.draw(win);
}

void UIManager::onClickListener(const sf::Vector2i &mouse_pos) {
    for (Button &b : buttons)
        b.onClick(mouse_pos);
}

std::vector<Button> UIManager::getButtons() const {
    return this->buttons;
}

void UIManager::addButton(Button &b) {
    this->buttons.push_back(b);
}

void UIManager::initUI() {
    Button b1(500, 100, 100, 50, "Test btn 1");
    b1.setOnClick([=]() { std::cout << "clicked: " << b1.text << '\n'; });

    addButton(b1);
}