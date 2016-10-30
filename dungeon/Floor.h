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

    Room *_startingRoom;
    Room *_exitRoom;

    std::map<int, std::map<int, Room * >> _rooms;

    std::vector<Corridor *> _corridors;

    void addRoom(Room *room);

    int roomCount();

    Room *getRandomRoomWithFreeEdge(std::vector<Coordinate *> coordinates, int tries);

    Coordinate *chooseFreeEdge(Coordinate *coordinate);

public:
    Floor(bool debug,Room * previous, int amountRooms, int roomsPerLock, bool last = false);

    ~Floor();

    Room *getStartingRoom() { return _startingRoom; };

    Room *getExitRoom() const { return _exitRoom; }

    int getMinX() { return minX; };

    int getMaxX() { return maxX; };

    int getMinY() { return minY; };

    int getMaxY() { return maxY; };

    Room *getRoom(int x, int y);

    const std::vector<Corridor *> &getCorridors() const { return _corridors; }

    const std::map<int, std::map<int, Room *>> *getRooms() const { return &_rooms; }
};


#endif //THE_ELDER_CODES_FLOOR_H
