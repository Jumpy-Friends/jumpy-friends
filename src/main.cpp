#include <raylib-cpp.hpp>

#include "game.hpp"

int main() {
    // Initialization
    int screenWidth = 1280;
    int screenHeight = 768;

    SetRandomSeed(std::time(0));

    Game* game = new Game(screenWidth, screenHeight, "Jumpy Friends");

    game->isHere();

    delete game;

    return 0;
}