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
        DM::showMap(_game->getCurrentFloor(), _game->getCurrentRoom(), _game->isDebug(),
                    _game->getPlayer()->getKeyLevel());
    } else {
        return false;
    }
    return true;
}

void MenuRoam::getViewScreen() {
    DM::showMap(_game->getCurrentFloor(), _game->getCurrentRoom(), _game->isDebug(), _game->getPlayer()->getKeyLevel(),
                true);

    DM::say("\nYou see the following exits:");

    Room *currentRoom = _game->getCurrentRoom();
    Room *targetRoom = currentRoom->getRoomBehindDoor(Direction::NORTH);
    if (targetRoom) {
        Room *validRoom = currentRoom->getRoomBehindDoor(Direction::NORTH, _game->getPlayer()->getKeyLevel());
        if (validRoom) {
            DM::say("\t An open door to the <n/north>.");
        } else {
            DM::say("\t A locked door to the north.");
        }
    }
    targetRoom = currentRoom->getRoomBehindDoor(Direction::EAST);
    if (targetRoom) {
        Room *validRoom = currentRoom->getRoomBehindDoor(Direction::EAST, _game->getPlayer()->getKeyLevel());
        if (validRoom) {
            DM::say("\t An open door to the <e/east>.");
        } else {
            DM::say("\t A locked door to the east.");
        }
    }
    targetRoom = currentRoom->getRoomBehindDoor(Direction::SOUTH);
    if (targetRoom) {
        Room *validRoom = currentRoom->getRoomBehindDoor(Direction::SOUTH, _game->getPlayer()->getKeyLevel());
        if (validRoom) {
            DM::say("\t An open door to the <s/south>.");
        } else {
            DM::say("\t A locked door to the south.");
        }
    }
    targetRoom = currentRoom->getRoomBehindDoor(Direction::WEST);
    if (targetRoom) {
        Room *validRoom = currentRoom->getRoomBehindDoor(Direction::WEST, _game->getPlayer()->getKeyLevel());
        if (validRoom) {
            DM::say("\t An open door to the <w/west>.");
        } else {
            DM::say("\t A locked door to the west.");
        }
    }
    if (currentRoom->getRoomType() == RoomType::DOWN) {
        //TODO BOSS BATTLE
        if (false) {
            DM::say("\t An open hatch to the next floor <d/down> below.");
        } else {
            DM::say("\t A locked hatch on the floor.");
        }
    }
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
