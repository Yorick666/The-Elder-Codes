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
#include "../enum/RoomCuriosity.h"
#include "../enum/RoomSize.h"

class Link;

class Room {

    Coordinate _coordinate;

    std::map<Direction, Corridor *> _doors;

    RoomType _type;
    int _securityLevel;
    bool _visited;

    std::vector<Monster> _monsters;

    RoomCuriosity _curiosity;
    RoomSize _size;

    std::map<Item *, int> _lootList;

public:
    Room(Coordinate coordinate, RoomType roomType, int securityLevel = 0);

    ~Room();

    Coordinate *getCoordinate() { return &_coordinate; }

    RoomType getRoomType() { return _type; }

    int getSecurityLevel() { return _securityLevel; }

    Room *getRoomBehindDoor(Direction direction, int securityLevel = -1);

    Corridor *getCorridorBehindDoor(Direction direction, int securityLevel = -1);

    void addDoor(Corridor *newCorridor, Direction direction = Direction::NORTH);

    void visit() { _visited = true; }

    bool visited() { return _visited; }

    void addMonster(Monster monster);

    void clearRoom();

    std::vector<Monster> *getMonsters() { return &_monsters; };

    bool hasMonsters();

    bool hasLivingMonsters();

    const RoomCuriosity &getRoomCuriosity() const { return _curiosity; }

    const RoomSize &getRoomSize() const { return _size; }

    void addItemToLootList(Item *item);

    void removeItemFromLootList(Item *item);

    std::map<Item *, int> *getLootList() { return &_lootList; }

    void setAsSecurityLevelUpgrade();
};


#endif //THE_ELDER_CODES_ROOM_H
