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

    if (coordinate.x == 0 && coordinate.y == 0) {
        throw 8;
    }


}

Room::~Room() {
    //TODO
}

void Room::addDoorTo(Room *newDoor) {

    Direction direction;

    if (this->getCoordinate()->x == newDoor->getCoordinate()->x &&
            this->getCoordinate()->y - newDoor->getCoordinate()->y == 1) {
        direction = Direction::NORTH;
    } else if (this->getCoordinate()->y == newDoor->getCoordinate()->y &&
            this->getCoordinate()->x - newDoor->getCoordinate()->x == -1) {
        direction = Direction::EAST;
    } else if (this->getCoordinate()->x == newDoor->getCoordinate()->x &&
            this->getCoordinate()->y - newDoor->getCoordinate()->y == -1) {
        direction = Direction::SOUTH;
    } else if (this->getCoordinate()->y == newDoor->getCoordinate()->y &&
            this->getCoordinate()->x - newDoor->getCoordinate()->x == 1) {
        direction = Direction::WEST;
    } else {
        direction = Direction::DOWN;
        throw -1; //TODO just a test;
    }

    if (_doors[direction]) {
        throw -1212;
    }

    _doors[direction] = newDoor;

    switch (direction){
        case Direction::NORTH:
            direction = Direction::SOUTH;
            break;
        case Direction::EAST:
            direction = Direction::WEST;
            break;
        case Direction::SOUTH:
            direction = Direction::NORTH;
            break;
        case Direction::WEST:
            direction = Direction::EAST;
            break;
        case Direction::DOWN:break;
    }

    if (!newDoor->getRoomBehindDoor(direction)) {
        newDoor->addDoorTo(this);
    } else if (newDoor->getRoomBehindDoor(direction) && newDoor->getRoomBehindDoor(direction) != this) {
        throw -2; //Existing link
    }
}

Room *Room::getRoomBehindDoor(Direction direction, int keyLevel) {
    Room *target = _doors[direction];
    if (target && (target->getKeyLevel() <= keyLevel || keyLevel == -1)) {
        return target;
    }
    return nullptr;
}


//std::map<Direction, Link *> Room::getLinks() {
//    map<Direction, Link *> result;
//
//    if (_north != nullptr) {
//        result[Direction::NORTH] = _north;
//    }
//    if (_east != nullptr) {
//        result[Direction::EAST] = _east;
//    }
//    if (_south != nullptr) {
//        result[Direction::SOUTH] = _south;
//    }
//    if (_west != nullptr) {
//        result[Direction::WEST] = _west;
//    }
//
//    return result;
//}
