//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_DUNGEON_H
#define THE_ELDER_CODES_DUNGEON_H

#include <vector>
#include "Floor.h"
#include "Room.h"
#include "../enum/Direction.h"

class Dungeon {
    std::vector<Floor *> _floors;

    std::vector<Corridor *> _stairs;

    int _currentLevel;

public:
    Dungeon(bool debug, int size, int roomsPerFloor, int roomsPerLock);

    ~Dungeon();

    Room *getStartingRoom() const { return _floors[_currentLevel]->getStartingRoom(); };

    Room *getExitRoom() const { return _floors[_currentLevel]->getExitRoom(); };

    Floor *getCurrentFloor() const { return _floors[_currentLevel]; };

    int getCurrentLevel() const { return _currentLevel; }

    Room *descend();

    Room *ascend();
};


#endif //THE_ELDER_CODES_DUNGEON_H
