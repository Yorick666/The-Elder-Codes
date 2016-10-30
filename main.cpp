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
//        game->startNewGame();

        do {
            game->showScreen();
            game->getInput();

        } while (game->getGameState() != GameState::EXITING && game->getGameState() != GameState::VICTORY);

        if (game->getGameState() == GameState::VICTORY) {
            DM::say("Gratz!!!!!",true);
        }
        delete game;
    } catch (exception &e) {
        cout << "Exception encountered: " << e.what() << endl;
    }

    return 0;
}