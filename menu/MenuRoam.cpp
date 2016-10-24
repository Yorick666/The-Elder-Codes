//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include <iostream>
#include "MenuRoam.h"
#include "../DM.h"

using namespace std;

bool MenuRoam::handleInput(std::string input) {
    if (regex_match(input, regex("n|north"))) {
        _game->getPlayer()->travel(Direction::NORTH);
    } else if (regex_match(input, regex("e|east"))) {
        _game->getPlayer()->travel(Direction::EAST);
    } else if (regex_match(input, regex("s|south"))) {
        _game->getPlayer()->travel(Direction::SOUTH);
    } else if (regex_match(input, regex("w|west"))) {
        _game->getPlayer()->travel(Direction::WEST);
    } else if (regex_match(input, regex("d|down"))) {
        _game->getPlayer()->travel(Direction::DOWN);
    } else if (regex_match(input, regex("map"))) {
        DM::showMap(_game->getCurrentFloor(), _game->getCurrentRoom(), _game->isDebug());
    } else {
        return false;
    }
    return true;
}

void MenuRoam::getViewScreen() {
    DM::showMap(_game->getCurrentFloor(), _game->getCurrentRoom(), _game->isDebug(), true);
}

void MenuRoam::loadOptions() {
//    _options.push_back("fight");
//    _options.push_back("run");
//    _options.push_back("search");
    _options.push_back("rest");
    _options.push_back("items");
    _options.push_back("map");
}

MenuRoam::MenuRoam(Game *game) : Menu(game) {
    loadOptions();
}

void MenuRoam::prepareForInput() {
    cout << "[Life:" << _game->getPlayer()->getCurrentHp() << "/" << _game->getPlayer()->getMaxHp() << "] >";
}
