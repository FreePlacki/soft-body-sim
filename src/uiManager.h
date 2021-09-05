/**
 * Stores all ui elements and performs operations on them
*/

#pragma once

#include <vector>
#include "button.h"


class UIManager {
public:
    UIManager();

    void draw(sf::RenderWindow &win);
    void onClickListener(const sf::Vector2i &mouse_pos);

    std::vector<Button> getButtons() const;
    void addButton(Button &b);

private:
    std::vector<Button> buttons;

private:
    void initUI();
};