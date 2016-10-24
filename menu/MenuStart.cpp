//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include <iostream>
#include "MenuStart.h"

using namespace std;

bool MenuStart::handleInput(std::string input) {
    if (regex_match(input, regex("debug"))) {
        cout << "Starting new game with debug mode on." << endl;
        _game->startNewGame(true);
    } else if (regex_match(input, regex("new"))) {
        cout << "Starting new game." << endl;
        _game->startNewGame();
    } else if (regex_match(input, regex("load"))) {
        cout << "Load function not implemented yet." << endl;
    } else if (regex_match(input, regex("credits"))) {
        cout << "Credits function not implemented yet. (Just made by me, Yorick, atm :P )" << endl;
    } else {
        return false;
    }
    return true;
}

void MenuStart::loadOptions() {
    _options.push_back("new");
    _options.push_back("load");
    _options.push_back("credits");
    _options.push_back("exit");
}

void MenuStart::getViewScreen() {
    cout << "The Elder Codes - Algorithm of Time " << endl << "Remember: Enter <exit> at anytime to exit the game." <<
    endl;
}

MenuStart::MenuStart(Game *game) : Menu(game) {
    loadOptions();
}
