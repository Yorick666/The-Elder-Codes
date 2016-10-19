//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_DUNGEON_H
#define THE_ELDER_CODES_DUNGEON_H

#include <vector>
#include "Floor.h"
#include "Room.h"

class Dungeon {
    std::vector<Floor> floors;
    Floor* currentFloor;
    Room* currentRoom;

public:
    Dungeon(int size = 5, int roomsPerFloor = 500, int roomsPerLock = 100);
    ~Dungeon() {};
    Floor *getCurrentFloor();
    Room *getCurrentRoom();
};


#endif //THE_ELDER_CODES_DUNGEON_H
