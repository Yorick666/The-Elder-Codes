#include <iostream>
#include <random>
#include "enum/GameState.h"
#include "Game.h"

using namespace std;

int main() {
    cout << "The Elder Codes - Algorithm of Time " << endl;
    cout << "Remeber: Enter <exit> at anytime to exit the game." << endl;

    try {
        Game game = Game();

        do {
            game.showScreen();
            game.getInput();

        } while (game.getGameState() == GameState::EXITING);
    } catch (exception &e) {
        cout << "Standard exception: " << e.what() << endl;
    }

//    delete DM::getInstance(); ??

    cin.ignore();

    return 0;
}