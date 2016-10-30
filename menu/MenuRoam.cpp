//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include <iostream>
#include "MenuRoam.h"
#include "../DM.h"
#include "../items/Consumable.h"
#include "../Rng.h"

using namespace std;

void MenuRoam::loadOptions() {
    _options.clear();
    if (_game->getCurrentRoom()->hasMonsters()) {
        if (_game->getCurrentRoom()->hasLivingMonsters()) {
            _options.push_back("attack [id]");
            _options.push_back("run");
        } else {
            _options.push_back("search");
            _options.push_back("rest");
        }
    } else {
        _options.push_back("rest");
    }
    _options.push_back("inventory");
    _options.push_back("stats");
    _options.push_back("map");

    if (_game->isDebug()) {
        _options.push_back("save");
    }
}

void MenuRoam::getViewScreen() {
    DM::showMap(_game->getCurrentFloor(), _game->getCurrentRoom(), _game->isDebug(),
                _game->getPlayer()->getSecurityLevel(),
                true);

    DM::say("\nYou see the following exits:");

    Room *currentRoom = _game->getCurrentRoom();
    Corridor *targetCorridor = currentRoom->getCorridorBehindDoor(Direction::NORTH);
    Room *targetRoom = currentRoom->getRoomBehindDoor(Direction::NORTH);
    if (targetRoom) {
        if (targetCorridor && !targetCorridor->isCollapsed()) {
            Room *validRoom = currentRoom->getRoomBehindDoor(Direction::NORTH, _game->getPlayer()->getSecurityLevel());
            if (validRoom) {
                DM::say("\t An open door to the <n/north>.");
            } else {
                DM::say("\t A locked door to the north.");
            }
        } else {
            DM::say("\tA caved-in corridor to the north.");
        }
    }
    targetCorridor = currentRoom->getCorridorBehindDoor(Direction::EAST);
    targetRoom = currentRoom->getRoomBehindDoor(Direction::EAST);
    if (targetRoom) {
        if (targetCorridor && !targetCorridor->isCollapsed()) {
            Room *validRoom = currentRoom->getRoomBehindDoor(Direction::EAST, _game->getPlayer()->getSecurityLevel());
            if (validRoom) {
                DM::say("\t An open door to the <e/east>.");
            } else {
                DM::say("\t A locked door to the east.");
            }
        } else {
            DM::say("\tA caved-in corridor to the east.");
        }
    }
    targetCorridor = currentRoom->getCorridorBehindDoor(Direction::SOUTH);
    targetRoom = currentRoom->getRoomBehindDoor(Direction::SOUTH);
    if (targetRoom) {
        if (targetCorridor && !targetCorridor->isCollapsed()) {
            Room *validRoom = currentRoom->getRoomBehindDoor(Direction::SOUTH, _game->getPlayer()->getSecurityLevel());
            if (validRoom) {
                DM::say("\t An open door to the <s/south>.");
            } else {
                DM::say("\t A locked door to the south.");
            }
        } else {
            DM::say("\tA caved-in corridor to the south.");
        }
    }
    targetCorridor = currentRoom->getCorridorBehindDoor(Direction::WEST);
    targetRoom = currentRoom->getRoomBehindDoor(Direction::WEST);
    if (targetRoom) {
        if (targetCorridor && !targetCorridor->isCollapsed()) {
            Room *validRoom = currentRoom->getRoomBehindDoor(Direction::WEST, _game->getPlayer()->getSecurityLevel());
            if (validRoom) {
                DM::say("\t An open door to the <w/west>.");
            } else {
                DM::say("\t A locked door to the west.");
            }
        } else {
            DM::say("\tA caved-in corridor to the west.");
        }
    }
    if (currentRoom->getRoomType() == RoomType::EXIT) {
        if (!_game->getCurrentRoom()->hasLivingMonsters()) {
            DM::say("\t A Locked Golden Gate.");
        } else {
            DM::say("\t An unlocked Golden Gate. Could this be the end?");
        }
    }
    if (currentRoom->getRoomType() == RoomType::DOWN) {
        if (!_game->getCurrentRoom()->hasLivingMonsters()) {
            DM::say("\t An open hatch to the next floor <d/down> below.");
        } else {
            DM::say("\t A locked hatch on the floor.");
        }
    }
    if (currentRoom->getRoomType() == RoomType::UP) {
        if (!_game->getCurrentRoom()->hasLivingMonsters()) {
            DM::say("\t An open hatch back to the previous floor <u/up>stairs.");
        } else {
            DM::say("\t A locked hatch on the ceiling.");
        }
    }

    if (currentRoom->hasMonsters()) {
        DM::say("\nYou see the following monsters:");
        const vector<Monster> *monsters = currentRoom->getMonsters();
        for (int i = 0; i < monsters->size(); ++i) {
            DM::say("\t<" + to_string(i + 1) + ">: " + monsters->at(i).getName() + " [" +
                    to_string(monsters->at(i).getCurrentHp()) + "/" +
                    to_string(monsters->at(i).getMaxHp()) + "]");
        }
    }
}

void MenuRoam::handleInput(std::string input) {
    if (regex_match(input, regex("u|up"))) {
        _game->readyRoom(Direction::UP);
        _game->getPlayer()->travel(Direction::UP);
    } else if (regex_match(input, regex("d|down"))) {
        if (_game->getCurrentRoom()->getRoomType() == RoomType::EXIT && !_game->getCurrentRoom()->hasLivingMonsters()) {
            _game->changeState(GameState::VICTORY);
        } else {
            _game->readyRoom(Direction::DOWN);
            _game->getPlayer()->travel(Direction::DOWN);
        }
    } else if (regex_match(input, regex("n|north"))) {
        _game->readyRoom(Direction::NORTH);
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
                    _game->getPlayer()->getSecurityLevel());
    } else if (regex_match(input, regex("a|attack|f|fight|kill"))) {
        if (_game->getCurrentRoom()->hasLivingMonsters()) {
            _game->changeState(GameState::FIGHTING);
        } else {
            DM::say("uhm, fight what exactly?");
        }
    } else if (regex_match(input, regex("r|run|flee"))) {
        _game->flee();
    } else if (regex_match(input, regex("i|inventory"))) {
        _game->changeState(GameState::INVENTORY);
    } else if (regex_match(input, regex("r|rest"))) {
        if (!_game->getCurrentRoom()->hasLivingMonsters()) {
            map<Item *, int> *inventory = _game->getPlayer()->getInventory();
            bool rested = false;
            for (map<Item *, int>::iterator item = inventory->begin(); item != inventory->end(); item++) {
                if (item->first->getItemType() == ItemType::CONSUMABLE) {
                    Consumable *consumable = (Consumable *) item->first;
                    if (consumable->getConsumableType() == ConsumableType::FOOD) {
                        consumable->use(_game->getPlayer());
                        item->second -= 1;
                        if (item->second == 0) {
                            inventory->erase(item->first);
                        }
                        rested = true;
                        if (Rng::roleDice(10) > 7) {
                            _game->generateMonsters(_game->getCurrentRoom());
                        }
                        break;
                    }
                }
            }
            if (!rested) {
                DM::say("You don't have any food, so resting won't help you a lot.");
            }
        } else {
            DM::say("Why try to rest here? Being brave is almost the same as being stupid.");
        }
    } else if (regex_match(input, regex("search"))) {
        if (!_game->getCurrentRoom()->hasLivingMonsters()) {
            _game->checkDeadMonsters();
        } else {
            DM::say("Do you really want to loot so bad?");
        }
    } else if (regex_match(input, regex("stats"))) {
        DM::say("TODO"); //TODO
    } else if (_game->isDebug() && regex_match(input, regex("save"))) {
        _game->savePlayer();
    } else {
        DM::say("Come again for big fudge?");
    }
}

MenuRoam::MenuRoam(Game *game) : Menu(game) {
//    loadOptions();
}

void MenuRoam::prepareForInput() {
    cout << "[Life:" << _game->getPlayer()->getCurrentHp() << "/" << _game->getPlayer()->getMaxHp() << "]>";
}
