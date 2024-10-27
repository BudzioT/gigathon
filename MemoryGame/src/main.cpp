#include "headers/game.h"


int main() {
    Game game;
    while (!game.end()) {
        game.displayMenu();
    }

    return 0;
}
