#include "game.h"

int main() {
    Game game;
    game.run();

    return 0;
}
// g++ main.cpp game.cpp note.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio //