//
// Created by Yorick on 18/10/2016.
//

#include "Room.h"
#include "../Rng.h"

using namespace std;

Room::Room(Coordinate coordinate, RoomType roomType, int securityLevel) {
    _coordinate = coordinate;
    _securityLevel = securityLevel;
    _type = roomType;
    _visited = false;

    if (coordinate.x == 0 && coordinate.y == 0) {
        throw 8;
    }

    _size = (RoomSize) Rng::getRandomIntBetween(0, 3);
    _curiosity = (RoomCuriosity) Rng::getRandomIntBetween(0, 10);
}

Room::~Room() {
}

void Room::addDoor(Corridor *newCorridor, Direction direction) {

    Room *newRoom = newCorridor->otherSide(this);

    if (direction == Direction::NORTH) {
        if (this->getCoordinate()->x == newRoom->getCoordinate()->x &&
            this->getCoordinate()->y - newRoom->getCoordinate()->y == 1) {
            direction = Direction::NORTH;
        } else if (this->getCoordinate()->y == newRoom->getCoordinate()->y &&
                   this->getCoordinate()->x - newRoom->getCoordinate()->x == -1) {
            direction = Direction::EAST;
        } else if (this->getCoordinate()->x == newRoom->getCoordinate()->x &&
                   this->getCoordinate()->y - newRoom->getCoordinate()->y == -1) {
            direction = Direction::SOUTH;
        } else if (this->getCoordinate()->y == newRoom->getCoordinate()->y &&
                   this->getCoordinate()->x - newRoom->getCoordinate()->x == 1) {
            direction = Direction::WEST;
        }
    }

    if (_doors[direction]) {
        delete _doors[direction];
        throw -1212;
    }

    _doors[direction] = newCorridor;
}

Room *Room::getRoomBehindDoor(Direction direction, int securityLevel) {
    Corridor *targetCorridor = _doors[direction];
    if (targetCorridor) {
        Room *target = targetCorridor->otherSide(this);
        if (target && (target->getSecurityLevel() <= securityLevel || securityLevel == -1)) {
            return target;
        }
    }

    return nullptr;
}

void Room::addMonster(Monster monster) {
    _monsters.push_back(monster);
}

void Room::clearRoom() {
    _monsters.clear();
}

bool Room::hasMonsters() {
    return !_monsters.empty();
}

bool Room::hasLivingMonsters() {
    int count = 0;
    for (int i = 0; i < _monsters.size(); ++i) {
        if (_monsters[i].getCurrentHp() > 0) {
            count++;
        }
    }
    return count > 0;
}

Corridor *Room::getCorridorBehindDoor(Direction direction, int securityLevel) {
    Corridor *targetCorridor = _doors[direction];
    if (targetCorridor) {
        Room *target = targetCorridor->otherSide(this);
        if (target && (target->getSecurityLevel() <= securityLevel || securityLevel == -1)) {
            return targetCorridor;
        }
    }

    return nullptr;
}

void Room::addItemToLootList(Item *item) {
    if (_lootList.find(item) == _lootList.end()) {
        _lootList[item] = 1;
    } else {
        _lootList[item] += 1;
    }
}

void Room::removeItemFromLootList(Item *item) {
    if (_lootList.find(item) != _lootList.end()) {
        if (_lootList[item] == 1) {
            _lootList.erase(item);
        } else if (_lootList[item] > 1) {
            _lootList[item] -= 1;
        }
    }
}

void Room::setAsSecurityLevelUpgrade() {
    if (_type == RoomType::NORMAL) {
        _type = RoomType::UPGRADE;
    }
}
