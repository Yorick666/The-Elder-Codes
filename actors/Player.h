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
    int _level;
    int _securityLevel;
    Room *_currentRoom;

public:
    Player(Room *currentRoom, std::string name, int hp = 10, int strength = 1, int dexterity = 1, int constitution = 1,
           int proficiencyBonus = 2, int level = 1, int experience = 30000);

    Player(Room *currentRoom, Player *loadedPlayer);

    ~Player() { }

    bool travel(Direction direction);

    Room *getCurrentRoom() const { return _currentRoom; };

    int getSecurityLevel() const { return _securityLevel; };

    void flee();

    void equip(const Item *item);

    int getLevel() const { return _level; }

    void gainExperience(const int exp);

    void checkForLevelUp();

    int getExperience() const { return _experience; }

    void unequip(Item *item);

    void upgradeSecurityLevel();
};


#endif //THE_ELDER_CODES_PLAYER_H
