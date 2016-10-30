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
    Player(Room *currentRoom, std::string name, int hp = 10, int strength = 2, int dexterity = 2, int constitution = 2,
           int proficiencyBonus = 2,
           int currentSecurityLevel = 0, int level = 1);

    void travel(Direction direction);

    Room *getCurrentRoom() const { return _currentRoom; };

    int getSecurityLevel() const { return _securityLevel; };

    void generateStartingGear(std::vector<Item *> *possibleGear);

    void flee();

    void equip(Item *item);

    int getLevel() const { return _level; }

    void gainExperience(int exp);

    void checkForLevelUp();
};


#endif //THE_ELDER_CODES_PLAYER_H
