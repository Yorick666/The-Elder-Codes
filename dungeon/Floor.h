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

    Room *startingRoom;
    Room *stairDown;

    std::vector<Coordinate *> roomCoordinates;
    std::map<int, std::map<int, Room * >> rooms;
    std::map<int, std::vector<Coordinate *>> levels;

    void addRoom(Room *room);

    int roomCount();

    Room *getRandomRoomWithFreeEdge(std::vector<Coordinate *> coordinates);

    Coordinate *chooseFreeEdge(Coordinate *coordinate);

public:
    Floor(bool debug, int amountRooms, Room *prev, int roomsPerLock, bool last = false);

    ~Floor() { }; //TODO

    Room *getStartingRoom() { return startingRoom; };

    Room *getStairsDown() { return stairDown; };

    int getMinX() { return minX; };

    int getMaxX() { return maxX; };

    int getMinY() { return minY; };

    int getMaxY() { return maxY; };

    Room *getRoom(int x, int y);
};


#endif //THE_ELDER_CODES_FLOOR_H
