//
// Created by Yorick on 18/10/2016.
//

#include "Room.h"

using namespace std;

Room::Room(Coordinate coordinate, RoomType roomType, int keyLevel) {
    _coordinate = coordinate;
    _keyLevel = keyLevel;
    _type = roomType;
    _visited = false;

    _north = nullptr;
    _south = nullptr;
    _east = nullptr;
    _west = nullptr;

    if (coordinate.x == 0 && coordinate.y == 0) {
        throw 8;
    }
}

Room::~Room() {
    //TODO
}

void Room::addLink(Link *newLink) {
    switch (newLink->getDirection(this)) {
        case Direction::NORTH:
            _north = newLink;
            break;
        case Direction::EAST:
            _east = newLink;
            break;
        case Direction::SOUTH:
            _south = newLink;
            break;
        case Direction::WEST:
            _west = newLink;
            break;
        case Direction::DOWN:
            throw 999; //TODO
    }
}

Link *Room::getLink(Direction direction) {
    switch (direction) {
        case Direction::NORTH:
            return _north;
        case Direction::EAST:
            return _east;
        case Direction::SOUTH:
            return _south;
        case Direction::WEST:
            return _west;
        case Direction::DOWN:
            return nullptr; //TODO
    }
}

std::map<Direction, Link *> Room::getLinks() {
    map<Direction, Link *> result;

    if (_north != nullptr) {
        result[Direction::NORTH] = _north;
    }
    if (_east != nullptr) {
        result[Direction::EAST] = _east;
    }
    if (_south != nullptr) {
        result[Direction::SOUTH] = _south;
    }
    if (_west != nullptr) {
        result[Direction::WEST] = _west;
    }

    return result;
}
