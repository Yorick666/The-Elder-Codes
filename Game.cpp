//
// Created by Yorick on 18/10/2016.
//

#include <iostream>
#include "Game.h"
#include "MenuFactory.h"

using namespace std;

Game::Game() {
    _state = GameState::STARTING;
    _menu = MenuFactory::getInstance()->getMenu(_state);
    dungeon = new Dungeon();
    currentFloor = dungeon->getCurrentFloor();
    currentRoom = dungeon->getCurrentRoom();
}

Game::~Game() {
    delete dungeon;
}

void Game::showScreen() {
    cout << _menu->getMenuScreen() << endl;
}

GameState Game::getGameState() {
    return _state;
}

void Game::getInput() {
    if (_state != GameState::STARTING) {
        cout << "[Life:" << 0 << "]";
    }
    cout << ">";
    cin >> _input;
}
