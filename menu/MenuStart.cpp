//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include "MenuStart.h"
#include "../DM.h"

using namespace std;

void MenuStart::handleInput(std::string input) {
    if (regex_match(input, regex("debug"))) {
        DM::say("Starting new game with debug mode on.", true);
        _game->startNewGame(true);
    } else if (regex_match(input, regex("new"))) {
        DM::say("Starting new game.", true);
        _game->startNewGame();
    } else if (regex_match(input, regex("load"))) {
        DM::say("Load function not implemented yet.\n");
    } else if (regex_match(input, regex("credits"))) {
        DM::say("Credits function not implemented yet. (Just made by me, Yorick, atm :P )\n"); //TODO
    }
}

void MenuStart::loadOptions() {
    _options.push_back("new");
    _options.push_back("load");
    _options.push_back("credits");
    _options.push_back("exit");
}

void MenuStart::getViewScreen() {
    DM::say("The Elder Codes - Algorithm of Time\nRemember: Enter <exit> at anytime to exit the game.");
}

MenuStart::MenuStart(Game *game) : Menu(game) {
}
