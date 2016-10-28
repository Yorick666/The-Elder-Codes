//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include <conio.h>
#include "Game.h"
#include "menu/MenuFactory.h"
#include "DM.h"
#include "Loader.h"
#include "Rng.h"

using namespace std;

Game::Game() {
    _items = Loader::loadArmor();
    _menu = nullptr;
    _dungeon = nullptr;
    _player = nullptr;
}

Game::~Game() {
    delete _menu;
    delete _dungeon;
    delete _player;
    for (int i = 0; i < _items.size(); ++i) {
        if (_items[i]) {
            delete _items[i];
        }
    }
}

void Game::showScreen() {
    _menu->getMenuScreen();
}

GameState Game::getGameState() {
    return _state;
}

void Game::getInput() {
    _menu->prepareForInput();
    _input = DM::askInput();
    if (_input != "exit") {
        _menu->handleInput(_input);
    } else {
        _state = GameState::EXITING;
    }
    if (_player->getCurrentHp() == 0) {
        DM::say("GAME OVER!!!!!!!!!!! MUHAHAHAHA");
        DM::getInstance()->showOutput();
        getch();
        _state = GameState::EXITING;
    }
}

void Game::changeState(GameState newState) {
    _state = newState;
    Menu *temp = MenuFactory::getMenu(this, newState);
    if (temp) {
        if (_menu) {
            delete _menu;
        }
        _menu = temp;
    }
}

void Game::startNewGame(bool debug, int size, int roomsPerFloor, int roomsPerLock) {
    debugMode = debug;

    if (_dungeon) {
        delete _dungeon;
    }
    _dungeon = new Dungeon(debug, size, roomsPerFloor, roomsPerLock);

    if (_player) {
        delete _player;
    }

    _player = new Player(_dungeon->getStartingRoom(), "Player");
    _player->generateStartingGear(&_items);

    generateMonsters(getCurrentRoom()); //TODO delete after finished debugging

    DM::say("Welcome hero, you're about to embark on a journey to defeat the master of this dungeon: The Dungeon Master. (Me!)");

    changeState(GameState::ROAMING);
}

void Game::generateMonsters(Room *room) {
    if (room->getMonsters()->size() > 0) {
        room->clearRoom();
        DM::say("New monsters enter the room....");
    }

    room->addMonster(new Monster("test", 100, 10, 3, 2, 0, 0, 10)); //TODO random monsters

}

void Game::flee() {
    if (getCurrentRoom()->hasLivingMonsters()) {
        int chance = Rng::roleDice(10);
        if (chance > 5) {
            _player->flee();
        } else {
            DM::say("You failed to flee, giving the monsters a chance to attack you.");
            monsterCombat();
        }
    } else {
        DM::say("Flee from what exactly?");
    }
}

void Game::monsterCombat() {
    vector<Monster *> *monsters = getCurrentRoom()->getMonsters();
    for (int m = 0; m < monsters->size(); ++m) {
        Monster *monster = monsters->at(m);
        monster->attack(_player);
    }
}

void Game::readyRoom(Direction direction) {
    if (!_player->getCurrentRoom()->hasLivingMonsters()) {
        if (Rng::roleDice(10) > 4) {
            Room *r = _player->getCurrentRoom()->getRoomBehindDoor(direction, _player->getSecurityLevel());
            if (r != nullptr) {
                generateMonsters(r);
            }
        }
    }
}
