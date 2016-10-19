#include <iostream>
#include <random>
#include "enum/GameState.h"
#include "DM.h"
#include "Game.h"
#include "Rng.h"

using namespace std;

int main() {
    cout << "The Elder Codes - Algorithm of Time " << endl;
    cout << "Remeber: Enter <exit> at anytime to exit the game." << endl;

    Game game = Game();

    do {
        game.showScreen();
        game.getInput();

    } while (game.getGameState() == GameState::EXITING);

//    delete DM::getInstance(); ??

    cin.ignore();

    return 0;
}