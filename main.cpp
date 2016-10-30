#include <iostream>
#include <random>
#include "enum/GameState.h"
#include "Game.h"
#include "DM.h"

using namespace std;

int main() {

    try {
        Game *game = new Game();

        game->changeState(GameState::STARTING);

        do {
            game->showScreen();
            game->getInput();

        } while (game->getGameState() != GameState::EXITING);
        delete game;
    } catch (exception &e) {
        cout << "Exception encountered: " << e.what() << endl;
    }

    return 0;
}