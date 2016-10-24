//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_PLAYER_H
#define THE_ELDER_CODES_PLAYER_H


#include "Actor.h"
#include "../dungeon/Room.h"
#include "../dungeon/Floor.h"

class Player : public Actor {
    int _experience;
    int _keyLevel;
    Room *_currentRoom;

public:
    Player(Room *currentRoom, std::string name, int hp = 10, int attack = 2, int defense = 2, int currentKeyLevel = 0);

    int getCurrentHp() { return _hp; };

    int getMaxHp() { return _maxHp; };

    int getKeyLevel() { return _keyLevel; };

    void travel(Direction direction);

    Room *getCurrentRoom() { return _currentRoom; };
};


#endif //THE_ELDER_CODES_PLAYER_H
