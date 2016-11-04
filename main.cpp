#include <iostream>
#include <random>
#include <conio.h>
#include "enum/GameState.h"
#include "Game.h"
#include "DM.h"

using namespace std;

int main() {

    try {
        Game game;

        game.changeState(GameState::STARTING);

        do {
            game.showScreen();
            game.getInput();

        } while (game.getGameState() != GameState::EXITING);
    } catch (exception &e) {
        cout << "Exception encountered: " << e.what() << endl;
        getch();
    }
    catch (int e) {
        cout << "Something went wrong while loading in your files.";
        getch();
    }

    return 0;
}