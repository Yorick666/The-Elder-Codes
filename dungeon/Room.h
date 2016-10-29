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
#include "Corridor.h"

class Link;

class Room {

    Coordinate _coordinate;

    std::map<Direction, Corridor *> _doors;

    RoomType _type;
    int _securityLevel;
    bool _visited;

    std::vector<Monster *> _monsters;

public:
    Room(Coordinate coordinate, RoomType roomType, int securityLevel = 0);

    ~Room();

    Coordinate *getCoordinate() { return &_coordinate; }

    RoomType getRoomType() { return _type; }

    int getSecurityLevel() { return _securityLevel; }

    Room *getRoomBehindDoor(Direction direction, int securityLevel = -1);

    Corridor * getCorridorBehindDoor(Direction direction, int securityLevel = -1);

    void addDoor(Corridor *newCorridor);

    void visit() { _visited = true; }

    bool visited() { return _visited; }

    void addMonster(Monster * monster);

    void clearRoom();

    std::vector<Monster *> *getMonsters() { return &_monsters; } //TODO BAD!!!!?

    bool hasMonsters();

    bool hasLivingMonsters();
};


#endif //THE_ELDER_CODES_ROOM_H
