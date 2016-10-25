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

    Room *startingRoom;

    std::map<int, std::map<int, Room * >> rooms;

    void addRoom(Room *room);

    int roomCount();

    Room *getRandomRoomWithFreeEdge(std::vector<Coordinate *> coordinates, int tries);

    Coordinate *chooseFreeEdge(Coordinate *coordinate);

public:
    Floor(bool debug, int amountRooms, int roomsPerLock, bool last = false);

    ~Floor();

    Room *getStartingRoom() { return startingRoom; };

    int getMinX() { return minX; };

    int getMaxX() { return maxX; };

    int getMinY() { return minY; };

    int getMaxY() { return maxY; };

    Room *getRoom(int x, int y);
};


#endif //THE_ELDER_CODES_FLOOR_H
