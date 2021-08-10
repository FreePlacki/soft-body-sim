/**
 * SFML app for simulating soft body interactions.
 * @file main.cpp
 * @version dev 10/08/2021
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <vector>
#include "../header/particle.h"
#include "../header/vector2.h"
#include "../header/window.h"
#include "../header/engine.h"

using std::cout;
using std::endl;

// TODO add small function comments

// Controls operations of the main program
int main() {
    Window win(WIDTH, HEIGHT, "Soft Body Sim", 60);
    Engine eng;

    eng.mainLoop(win.getWin());

    return 0;
}
