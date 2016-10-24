#include <iostream>
#include <random>
#include "enum/GameState.h"
#include "Game.h"

using namespace std;

int main() {

    Game *game;

    try {
        game = new Game();

        do {
            cout << endl;
            game->showScreen();
            game->getInput();

        } while (game->getGameState() != GameState::EXITING);
    } catch (exception &e) {
        cout << "Exception encountered: " << e.what() << endl;
    }

//    delete DM::getInstance(); ??

    return 0;
}