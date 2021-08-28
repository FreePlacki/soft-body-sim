/**
 * SFML app for simulating soft body interactions.
 * @file main.cpp
 * @version dev 26/08/2021
*/

#include "window.h"
#include "engine.h"
#include "fileManager.h"


int main() {
    FileManager f;

    Window win(f.getCurrentSettings());
    Engine eng(win);

    eng.mainLoop();

    return 0;
}
