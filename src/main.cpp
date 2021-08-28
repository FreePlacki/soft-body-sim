/**
 * SFML app for simulating soft body dynamics.
 * @version dev 28/08/2021
*/

#include "window.h"
#include "engine.h"
#include "fileManager.h"


int main() {
    FileManager fm;

    Window win(fm.getCurrentSettings());
    Engine eng(win);

    eng.mainLoop();

    return 0;
}
