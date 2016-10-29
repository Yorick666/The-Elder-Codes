//
// Created by Yorick on 18/10/2016.
//

#include "Floor.h"
#include "../Rng.h"
#include "../DM.h"

using namespace std;

Floor::Floor(bool debug, int amountRooms, int roomsPerLock, bool last) {
    vector<Coordinate *> roomCoordinates;
    map<int, vector<Coordinate *>> levels;
    bool validFloor = false;

    while (!validFloor) {

        try {
            int x = amountRooms / 2;
            int y = amountRooms / 2;

            maxX = x;
            minX = x;
            maxY = y;
            minY = y;
            Room *firstRoom = new Room(Coordinate(x, y), RoomType::NORMAL);
            addRoom(firstRoom);
            roomCoordinates.push_back(firstRoom->getCoordinate());
            levels[0].push_back(firstRoom->getCoordinate());
            _startingRoom = firstRoom;

            int currentSecurityLevel = 0;

            while (roomCount() < amountRooms) {

                bool doLock = false;
                bool validRoom = true;

                if (levels[currentSecurityLevel].size() >= roomsPerLock && roomsPerLock > 0) {
                    ++currentSecurityLevel;
                    doLock = true;
                }

                Room *parent = nullptr;
                Coordinate newRoomCoordinate;
                while (newRoomCoordinate.x == 0 && newRoomCoordinate.y == 0) {
                    parent = nullptr;
                    if (!doLock && Rng::getRandomIntBetween(0, 10) > 0 && levels[currentSecurityLevel].size() > 0) {
                        parent = getRandomRoomWithFreeEdge(levels[currentSecurityLevel], amountRooms);
                    }
                    if (parent == nullptr) {
                        parent = getRandomRoomWithFreeEdge(roomCoordinates, amountRooms);
                        doLock = true;
                    }
                    if (parent != nullptr) {
                        Coordinate *tempCoordinate = chooseFreeEdge(parent->getCoordinate());
                        if (tempCoordinate) {
                            newRoomCoordinate.x = tempCoordinate->x;
                            newRoomCoordinate.y = tempCoordinate->y;
                        } else {
                            parent = nullptr;
                        }
                        delete tempCoordinate;
                    }

                }

                for (int i = 0; i < roomCoordinates.size(); ++i) {
                    if (roomCoordinates[i]->x == newRoomCoordinate.x &&
                        roomCoordinates[i]->y == newRoomCoordinate.y) {
                        validRoom = false;
                        break;
                    }
                }


                if (validRoom) {
                    Room *newRoom = nullptr;

                    if (roomCount() + 1 == amountRooms) {
                        if (last) {
                            newRoom = new Room(newRoomCoordinate, RoomType::EXIT, currentSecurityLevel);
                        } else {
                            newRoom = new Room(newRoomCoordinate, RoomType::DOWN, currentSecurityLevel);
                        }
                    } else {
                        newRoom = new Room(newRoomCoordinate, RoomType::NORMAL, currentSecurityLevel);
                    }

                    addRoom(newRoom);
                    if (debug) {
                        newRoom->visit();
                    }

                    roomCoordinates.push_back(newRoom->getCoordinate());
                    levels[currentSecurityLevel].push_back(newRoom->getCoordinate());
                    if (roomCount() > 1 && parent) {
                        _corridors.push_back(new Corridor(parent, newRoom));
                    }
                }
            }

            int extraLinks = (int) (amountRooms * 0.15) + 1;

            for (int l = 0; l < extraLinks; ++l) {
                bool linked = false;
                while (!linked) {
                    int randomX = Rng::getRandomIntBetween(0, _rooms.size() - 1);
                    int randomY = Rng::getRandomIntBetween(0, _rooms[randomX].size() - 1);

                    if (randomX < 0 || randomY < 0 || _rooms[randomX][randomY] == nullptr) {
                        continue;
                    }

                    Room *origin = _rooms[randomX][randomY];

                    if (origin->getRoomBehindDoor(Direction::NORTH) && origin->getRoomBehindDoor(Direction::EAST) &&
                        origin->getRoomBehindDoor(Direction::SOUTH) && origin->getRoomBehindDoor(Direction::WEST)) {
                        continue;
                    }

                    int dx = 0;
                    int dy = 0;

                    for (int i = 0; i < 10; ++i) {
                        Direction direction;
                        switch (Rng::roleDice(Dice::d4)) {
                            case 1:
                                direction = Direction::NORTH;
                                dx = 0;
                                dy = -1;
                                break;
                            case 2:
                                direction = Direction::EAST;
                                dx = 1;
                                dy = 0;
                                break;
                            case 3:
                                direction = Direction::SOUTH;
                                dx = 0;
                                dy = 1;
                                break;
                            case 4:
                                direction = Direction::WEST;
                                dx = -1;
                                dy = 0;
                                break;
                            default:
                                throw 132;
                        }
                        if (!origin->getRoomBehindDoor(direction) && _rooms[randomX + dx][randomY + dy] != nullptr &&
                            dx != dy) {
                            _corridors.push_back(new Corridor(origin, _rooms[randomX + dx][randomY + dy]));
                            linked = true;
                        }
                    }
                }
            }

            validFloor = true;
        } catch (int e) {
            DM::say("Error: " + to_string(e) + " !!!");
            DM::say("Restarting Generator...");
            for (int x = 0; x < _rooms.size(); ++x) {
                for (int y = 0; y < _rooms[x].size(); ++y) {
                    delete _rooms[x][y];
                }
            }
            _rooms.clear();
            roomCoordinates.clear();
            levels.clear();
            _startingRoom = nullptr;
        }

    }
}

void Floor::addRoom(Room *room) {
    if (_rooms[room->getCoordinate()->x][room->getCoordinate()->y]) {
        delete _rooms[room->getCoordinate()->x][room->getCoordinate()->y];
        //TODO ever?
    }
    _rooms[room->getCoordinate()->x][room->getCoordinate()->y] = room;
    if (room->getCoordinate()->x < minX)
        minX = room->getCoordinate()->x;
    if (room->getCoordinate()->x > maxX)
        maxX = room->getCoordinate()->x;
    if (room->getCoordinate()->y < minY)
        minY = room->getCoordinate()->y;
    if (room->getCoordinate()->y > maxY)
        maxY = room->getCoordinate()->y;
}

int Floor::roomCount() {
    int roomCount = 0;

    for (auto x : _rooms) {
        for (auto y : x.second) {
            ++roomCount;
        }
    }

    return roomCount;
}

Room *Floor::getRandomRoomWithFreeEdge(vector<Coordinate *> coordinates, int tries) {
    while (tries > 0) {
        signed int rand = Rng::getRandomIntBetween(0, coordinates.size() - 1);
        Coordinate *coordinate = coordinates.at(rand);

        if (_rooms.count(coordinate->x - 1) == 0 || _rooms.count(coordinate->x + 1) == 0 ||
            _rooms[coordinate->x - 1].count(coordinate->y) == 0 ||
            _rooms[coordinate->x + 1].count(coordinate->y) == 0 ||
            _rooms[coordinate->x].count(coordinate->y - 1) == 0 ||
            _rooms[coordinate->x].count(coordinate->y + 1) == 0) {
            return _rooms[coordinate->x][coordinate->y];
        }
        --tries;
    }

    return nullptr;
}

Coordinate *Floor::chooseFreeEdge(Coordinate *coordinate) {
    for (int tries = 0; tries < 20; ++tries) {
        int randomDirection = Rng::getRandomIntBetween(1, 4);
        if (randomDirection == 1) {
            if (_rooms.count(coordinate->x - 1) == 0 || _rooms[coordinate->x - 1].count(coordinate->y) == 0) {
                return new Coordinate(coordinate->x - 1, coordinate->y);
            }
        }
        if (randomDirection == 2) {
            if (_rooms.count(coordinate->x + 1) == 0 || _rooms[coordinate->x + 1].count(coordinate->y) == 0) {
                return new Coordinate(coordinate->x + 1, coordinate->y);
            }
        }
        if (randomDirection == 3) {
            if (_rooms[coordinate->x].count(coordinate->y - 1) == 0) {
                return new Coordinate(coordinate->x, coordinate->y - 1);
            }
        }
        if (randomDirection == 4) {
            if (_rooms[coordinate->x - 1].count(coordinate->y + 1) == 0) {
                return new Coordinate(coordinate->x, coordinate->y + 1);
            }
        }
    }
    return nullptr;
}

Room *Floor::getRoom(int x, int y) {
    return _rooms[x][y];
}

Floor::~Floor() {
    for (int x = 0; x < _rooms.size(); ++x) {
        for (int y = 0; y < _rooms[x].size(); ++y) {
            if (_rooms[x][y]) {
                delete _rooms[x][y];
            }
        }
    }
//    if (_startingRoom) {
//        delete _startingRoom;
//    }
}
