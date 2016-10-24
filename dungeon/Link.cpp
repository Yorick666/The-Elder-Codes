//
// Created by Yorick on 19/10/2016.
//

#include "Link.h"

Link::Link(Room *origin, Room *target, int keyLevel) {
    if (!origin || !target) {
        throw 6;
    }

    _origin = origin;
    _target = target;

    if (origin->getCoordinate()->x == target->getCoordinate()->x &&
        origin->getCoordinate()->y - target->getCoordinate()->y == 1) {
        _direction = Direction::NORTH;
    } else if (origin->getCoordinate()->y == target->getCoordinate()->y &&
               origin->getCoordinate()->x - target->getCoordinate()->x == -1) {
        _direction = Direction::EAST;
    } else if (origin->getCoordinate()->x == target->getCoordinate()->x &&
               origin->getCoordinate()->y - target->getCoordinate()->y == -1) {
        _direction = Direction::SOUTH;
    } else if (origin->getCoordinate()->y == target->getCoordinate()->y &&
               origin->getCoordinate()->x - target->getCoordinate()->x == 1) {
        _direction = Direction::WEST;
    } else {
        _direction = Direction::DOWN;
        throw -1; //TODO just a test;
    }

    _origin->addLink(this);
    _target->addLink(this);
    _keyLevel = keyLevel;

}

Room *Link::travel(Room *origin, int keyLevel) {
    if (_origin == origin && (keyLevel >= _keyLevel || _target->visited())) {
        _traveled = true;
        return _target;
    }

    if (_target == origin && (keyLevel >= _keyLevel || _target->visited())) {
        _traveled = true;
        return _origin;
    }

    return nullptr;
}

Direction Link::getDirection(Room *origin) {
    if (_origin == origin) {
        return _direction;
    }

    if (_target == origin) {
        if (_direction == Direction::NORTH) {
            return Direction::SOUTH;
        } else if (_direction == Direction::EAST) {
            return Direction::WEST;
        } else if (_direction == Direction::SOUTH) {
            return Direction::NORTH;
        } else if (_direction == Direction::WEST) {
            return Direction::EAST;
        }
    }
    return Direction::DOWN;
}
