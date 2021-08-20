/**
 * SFML app for simulating soft body interactions.
 * @file main.cpp
 * @version dev 18/08/2021
*/

#include "engine/window.h"
#include "engine/engine.h"
#include "engine/fileManager.h"

// TODO static keyword
int main() {
    FileManager f;

    Window win(f.getCurrentSettings());
    Engine eng(win);

    eng.mainLoop();

    return 0;
}
