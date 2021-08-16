/**
 * SFML app for simulating soft body interactions.
 * @file main.cpp
 * @version dev 15/08/2021
*/

#include "../header/window.h"
#include "../header/engine.h"
#include "../header/fileManager.h"


int main() {
    // TODO implement a wrapper for those operations
    FileManager f;

    Window win(f.getCurrentSettings());
    Engine eng(win);

    eng.mainLoop();

    return 0;
}
