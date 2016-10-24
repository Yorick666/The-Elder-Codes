//
// Created by Yorick on 18/10/2016.
//
#include "Player.h"
#include "../DM.h"

using namespace std;

Player::Player(Room *currentRoom, string name, int hp, int attack, int defense,
               int currentKeyLevel) : Actor(name,
                                            hp,
                                            attack,
                                            defense) {
    _keyLevel = currentKeyLevel;
    _currentRoom = currentRoom;
    currentRoom->visit();
}

void Player::travel(Direction direction) {
    Room *r = _currentRoom->getRoomBehindDoor(direction, _keyLevel);
    if (r != nullptr) {
        _currentRoom = r;
        _currentRoom->visit();
    } else {
        DM::say("You can't travel in this direction.");
    }
}
