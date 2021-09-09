/**
 * SFML app for simulating soft body dynamics.
*/

#include "window.h"
#include "engine.h"
#include "fileManager.h"


int main() {
    std::unique_ptr<FileManager> fm = std::make_unique<FileManager>();

    std::unique_ptr<Window> win = std::make_unique<Window>((*fm).getCurrentSettings());
    std::unique_ptr<Engine> eng = std::make_unique<Engine>(std::move(win));

    (*eng).mainLoop();

    return 0;
}
