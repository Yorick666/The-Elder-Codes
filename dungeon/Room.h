//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_ROOM_H
#define THE_ELDER_CODES_ROOM_H

#include <map>
#include <vector>
#include "Coordinate.h"
#include "Link.h"
#include "../enum/RoomType.h"
#include "../enum/Direction.h"
#include "../actors/Monster.h"

class Link;

class Room {

    Coordinate _coordinate;

    Link *_north;
    Link *_south;
    Link *_east;
    Link *_west;

    RoomType _type;
    int _keyLevel;
    bool _visited;

    std::vector<Monster *> _monsters;
    std::vector<Actor *> _combatQueue;

public:
    Room() { throw 9; }

    Room(Coordinate coordinate, RoomType roomType, int keyLevel = 0);

    ~Room();

    Coordinate *getCoordinate() { return &_coordinate; }

    RoomType getRoomType() { return _type; }

    int getKeyLevel() { return _keyLevel; }

    Link *getLink(Direction direction);

    std::map<Direction, Link *> getLinks();

    void addLink(Link *newLink);

    void visit() { _visited = true; }

    bool visited() { return _visited; }
};


#endif //THE_ELDER_CODES_ROOM_H
