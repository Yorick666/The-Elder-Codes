//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_ROOM_H
#define THE_ELDER_CODES_ROOM_H

#include <map>
#include <vector>
#include "Coordinate.h"
#include "../enum/RoomType.h"
#include "../enum/Direction.h"
#include "../actors/Monster.h"

class Link;

class Room {

    Coordinate _coordinate;

    std::map<Direction, Room*> _doors;

    RoomType _type;
    int _keyLevel;
    bool _visited;

    std::vector<Monster *> _monsters;
    std::vector<Actor *> _combatQueue;

public:
    Room(Coordinate coordinate, RoomType roomType, int keyLevel = 0);

    ~Room();

    Coordinate *getCoordinate() { return &_coordinate; }

    RoomType getRoomType() { return _type; }

    int getKeyLevel() { return _keyLevel; }

    Room *getRoomBehindDoor(Direction direction, int keylevel = -1);

    void addDoorTo(Room *newdoor);

    void visit() { _visited = true; }

    bool visited() { return _visited; }
};


#endif //THE_ELDER_CODES_ROOM_H
