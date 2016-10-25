//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include "Game.h"
#include "menu/MenuFactory.h"
#include "DM.h"

using namespace std;

Game::Game() {
    _menu = nullptr;
    _dungeon = nullptr;
    _player = nullptr;
}

Game::~Game() {
    delete _menu;
    delete _dungeon;
    delete _player;
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
    changeState(GameState::ROAMING);
    debugMode = debug;

    if (_dungeon) {
        delete _dungeon;
    }
    _dungeon = new Dungeon(debug, size, roomsPerFloor, roomsPerLock);

    if (_player){
        delete _player;
    }

    _player = new Player(_dungeon->getStartingRoom(), "Player");

    DM::say("Welcome hero, you're about to embark on a journey to defeat the master of this dungeon: The Dungeon Master. \n ");
}
