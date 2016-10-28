//
// Created by Yorick on 18/10/2016.
//

#include "Room.h"

using namespace std;

Room::Room(Coordinate coordinate, RoomType roomType, int securityLevel) {
    _coordinate = coordinate;
    _securityLevel = securityLevel;
    _type = roomType;
    _visited = false;

    if (coordinate.x == 0 && coordinate.y == 0) {
        throw 8;
    }


}

Room::~Room() {
    //TODO
    for (int i = 0; i < _monsters.size(); ++i) {
        if (_monsters[i]) {
            delete _monsters[i];
        }
    }
}

void Room::addDoorTo(Room *newDoor) {

    Direction direction = Direction::DOWN;

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
    }

    if (_doors[direction]) {
        delete _doors[direction];
//        throw -1212;
    }

    _doors[direction] = newDoor;

    switch (direction) {
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
    }

    if (!newDoor->getRoomBehindDoor(direction)) {
        newDoor->addDoorTo(this);
    }
}

Room *Room::getRoomBehindDoor(Direction direction, int securityLevel) {
    Room *target = _doors[direction];
    if (target && (target->getSecurityLevel() <= securityLevel || securityLevel == -1)) {
        return target;
    }
    return nullptr;
}

void Room::addMonster(Monster * monster) {
    _monsters.push_back(monster);
}

void Room::clearRoom() {
    for (int i = 0; i < _monsters.size(); ++i) {
        if (_monsters[i]) {
            delete _monsters[i];
        }
    }
    _monsters.clear();
}

bool Room::hasMonsters() {
    return !_monsters.empty();
}

bool Room::hasLivingMonsters() {
    int count = 0;
    for (int i = 0; i < _monsters.size(); ++i) {
        if (_monsters[i] ->getCurrentHp() > 0) {
            count++;
        }
    }
    return count > 0;
}
