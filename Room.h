//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_ROOM_H
#define THE_ELDER_CODES_ROOM_H

#include <vector>
#include "Coordinate.h"
#include "enum/RoomType.h"
#include "Link.h"

class Link;

class Room {

    Coordinate _coordinate;
    std::vector<Link *> _links;
    RoomType _type;
    int _keyLevel;
    bool _visited;

public:
    Room() { throw 9; };

    Room(Coordinate coordinate, RoomType roomType, int keyLevel = 0);

    ~Room();

    Coordinate *getCoordinate() { return &_coordinate; };

    RoomType getRoomType() { return _type; };

    int getKeyLevel() { return _keyLevel; };

    void addLink(Link *link) { _links.push_back(link); };

    void visit() { _visited = true; };
};


#endif //THE_ELDER_CODES_ROOM_H
