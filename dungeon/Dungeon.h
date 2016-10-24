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
    std::vector<Floor> floors;
    Floor* _currentFloor;
    Room* _currentRoom;

public:
    Dungeon(bool debug, int size, int roomsPerFloor, int roomsPerLock);
    ~Dungeon() {}; //TODO
    Floor *getCurrentFloor();
    Room *getCurrentRoom();
    void drawSurroundings(bool debug = false);
    void drawMap(bool debug = false);
    void travel(Direction direction, int keyLevel);
};


#endif //THE_ELDER_CODES_DUNGEON_H
