//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_FLOOR_H
#define THE_ELDER_CODES_FLOOR_H

#include <map>
#include <vector>
#include "Room.h"

class Floor {
    int maxX;
    int minX;
    int maxY;
    int minY;

    int _amountRooms;

    Room *stairUp;
    Room *stairDown;

    std::vector<Coordinate *> roomCoordinates;
    std::map<int, std::map<int, Room* >> rooms;
    std::map<int, std::vector<Coordinate *>> levels;

    void addRoom(Room *room);

    int roomCount();

    Room *getRandomRoomWithFreeEdge(std::vector<Coordinate *> coordinates);

    Coordinate *chooseFreeEdge(Coordinate *coordinate);

    void linkRooms(Room *room1, Room *room2, int keyLevel);

public:
    Floor(int amountRooms, Room *prev, int roomsPerLock, bool last = false);

    Room *getStairsUp() { return stairUp; };

    Room *getStairsDown() { return stairDown; };

    void drawFloor();
};


#endif //THE_ELDER_CODES_FLOOR_H
