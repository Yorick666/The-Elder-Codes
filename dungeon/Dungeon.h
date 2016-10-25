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
    std::vector<Floor *> floors;

    int currentLevel;

public:
    Dungeon(bool debug, int size, int roomsPerFloor, int roomsPerLock);

    ~Dungeon();

    Room *getStartingRoom() { return floors[currentLevel]->getStartingRoom(); };

    Floor *getCurrentFloor() { return floors[currentLevel]; };

    Room * descend();
};


#endif //THE_ELDER_CODES_DUNGEON_H
