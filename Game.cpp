//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include "Game.h"
#include "menu/MenuFactory.h"
#include "DM.h"

using namespace std;

Game::Game() {
    changeState(GameState::STARTING);
}

Game::~Game() {
    delete dungeon;
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
    if (_state != newState) {
        _state = newState;
        _menu = MenuFactory::getMenu(this, newState);
    }
}

void Game::startNewGame(bool debug, int size, int roomsPerFloor, int roomsPerLock) {
    changeState(GameState::ROAMING);
    debugMode = debug;
    dungeon = new Dungeon(debug, size, roomsPerFloor, roomsPerLock);

    _player = new Player("Player");
}