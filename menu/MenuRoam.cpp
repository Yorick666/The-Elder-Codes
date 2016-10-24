//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include <iostream>
#include "MenuRoam.h"

using namespace std;

bool MenuRoam::handleInput(std::string input) {
    if (regex_match(input, regex("n|north"))) {
        _game->getDungeon()->travel(Direction::NORTH,
                                    _game->getPlayer()->getKeyLevel()); // TODO beter 1 laag aan kennis?
    } else if (regex_match(input, regex("e|east"))) {
        _game->getDungeon()->travel(Direction::EAST, _game->getPlayer()->getKeyLevel());
    } else if (regex_match(input, regex("s|south"))) {
        _game->getDungeon()->travel(Direction::SOUTH, _game->getPlayer()->getKeyLevel());
    } else if (regex_match(input, regex("w|west"))) {
        _game->getDungeon()->travel(Direction::WEST, _game->getPlayer()->getKeyLevel());
    } else if (regex_match(input, regex("d|down"))) {
        _game->getDungeon()->travel(Direction::DOWN, _game->getPlayer()->getKeyLevel());
    } else if (regex_match(input, regex("map"))) {
        _game->getDungeon()->drawMap(_game->isDebug());
    } else {
        return false;
    }
    return true;
}

void MenuRoam::getViewScreen() {
    _game->getDungeon()->drawSurroundings(_game->isDebug());
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
