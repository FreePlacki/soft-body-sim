/**
 * SFML app for simulating soft body interactions.
 * @file main.cpp
 * @version dev 15/08/2021
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <vector>
#include "../header/particle.h"
#include "../header/vector2.h"
#include "../header/window.h"
#include "../header/engine.h"


#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define MAX_FPS 120

// TODO add small function comments

// Controls operations of the main program
int main() {
    Window win(WIN_WIDTH, WIN_HEIGHT, "Soft Body Sim", MAX_FPS);
    Engine eng(win);

    eng.mainLoop();

    return 0;
}
