//
// Created by Yorick on 18/10/2016.
//

#include <c++/iostream>
#include "Floor.h"
#include "Rng.h"

using namespace std;

Floor::Floor(int amountRooms, Room *prev, int roomsPerLock, bool last) {
    bool validFloor = false;

    _amountRooms = amountRooms;

    while (!validFloor) {

        try {
            int x = amountRooms / 2;
            int y = amountRooms / 2;

            maxX = x;
            minX = x;
            maxY = y;
            minY = y;
            Coordinate *coordinate = new Coordinate(x, y);
            Room *firstRoom = new Room(coordinate, nullptr, RoomType::UP);
            addRoom(firstRoom);
            roomCoordinates.push_back(coordinate);
            levels[0].push_back(coordinate);
            stairUp = firstRoom;


            int keyLevel = 0; //Number of keys required to get to new room

            // ADDING OTHER ROOMS
            while (roomCount() < amountRooms) {
                bool doLock = false;

                if (levels[keyLevel].size() >= roomsPerLock && roomsPerLock > 0) {
                    ++keyLevel;
                    doLock = true;
                }

                Room *parent;
                Coordinate *newRoomCoordinate = nullptr;
                while (newRoomCoordinate == nullptr) {
                    parent = nullptr;
                    if (!doLock && Rng::getInstance()->randomIntBetween(0, 10) > 0) {
                        parent = getRandomRoomWithFreeEdge(levels[keyLevel]);
                    }
                    if (parent == nullptr) {
                        parent = getRandomRoomWithFreeEdge(roomCoordinates);
                        doLock = true;
                    }

                    if (parent != nullptr) {
                        newRoomCoordinate = chooseFreeEdge(parent->getCoordinate());
                    }

                }

                Room *newRoom;

                if (roomCount() + 1 == _amountRooms) {
                    newRoom = new Room(newRoomCoordinate, parent, RoomType::DOWN, keyLevel);
                    stairDown = newRoom;
                } else {
                    newRoom = new Room(newRoomCoordinate, parent, RoomType::NORMAL, keyLevel);
                }

                addRoom(newRoom);
                roomCoordinates.push_back(newRoomCoordinate);
                levels[keyLevel].push_back(newRoomCoordinate);

//                parent->addChild(newRoom);

                linkRooms(parent, newRoom, doLock && keyLevel > 0 ? keyLevel : 0);

//                cout << roomCount() << endl;
            }
            validFloor = true;
        } catch (int e) {
            cout << e << endl;
            cout << "Restarting Generator...\n\n";
            rooms.clear();
            roomCoordinates.clear();
            levels.clear();
            stairUp = nullptr;
            stairDown = nullptr;
        }

    }
}

void Floor::addRoom(Room *room) {
    rooms[room->getCoordinate()->x][room->getCoordinate()->y] = room;
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

    for (auto x : rooms) {
        for (auto y : x.second) {
            ++roomCount;
        }
    }

    return roomCount;
}

Room *Floor::getRandomRoomWithFreeEdge(vector<Coordinate *> coordinates) {
    int tries = 0;
    while (tries < _amountRooms / 10) {
        Coordinate *coordinate = coordinates.at(Rng::getInstance()->randomIntBetween(0, coordinates.size() - 1));
        if (rooms.count(coordinate->x - 1) == 0 || rooms.count(coordinate->x + 1) == 0 ||
            rooms[coordinate->x - 1].count(coordinate->y) == 0 || rooms[coordinate->x + 1].count(coordinate->y) == 0 ||
            rooms[coordinate->x].count(coordinate->y - 1) == 0 || rooms[coordinate->x].count(coordinate->y + 1) == 0) {
            return rooms[coordinate->x][coordinate->y];
        }
        ++tries;
    }

    return nullptr;
}

Coordinate *Floor::chooseFreeEdge(Coordinate *coordinate) {
    for (int tries = 0; tries < 20; ++tries) {
        int randomDirection = Rng::getInstance()->randomIntBetween(1, 4);
        if (randomDirection == 1) {
            if (rooms.count(coordinate->x - 1) == 0 || rooms[coordinate->x - 1].count(coordinate->y) == 0) {
                return new Coordinate(coordinate->x - 1, coordinate->y);
            }
        }
        if (randomDirection == 2) {
            if (rooms.count(coordinate->x + 1) == 0 || rooms[coordinate->x + 1].count(coordinate->y) == 0) {
                return new Coordinate(coordinate->x + 1, coordinate->y);
            }
        }
        if (randomDirection == 3) {
            if (rooms[coordinate->x].count(coordinate->y - 1) == 0) {
                return new Coordinate(coordinate->x, coordinate->y - 1);
            }
        }
        if (randomDirection == 4) {
            if (rooms[coordinate->x - 1].count(coordinate->y + 1) == 0) {
                return new Coordinate(coordinate->x, coordinate->y + 1);
            }
        }
    }

    return nullptr;
}

void Floor::linkRooms(Room *room1, Room *room2, int keyLevel) {
//    cout << "future linking for Room(" << room1->getCoordinate()->x << "," << room1->getCoordinate()->y <<
//    ") and Room(" << room2->getCoordinate()->x << "," << room2->getCoordinate()->y << ") ";
//    cout << "with condition: " << keyLevel << endl;
    Link *newLink = new Link(room1, room2, keyLevel);
    room1->addLink(newLink);
    room2->addLink(newLink);
}

void Floor::drawFloor() {
    for (int y = minY - 2; y <= maxY + 2; ++y) {
        for (int x = minX - 2; x <= maxX + 2; ++x) {
            if (rooms[x][y] == nullptr) {
                cout << ".";
            } else {
                if (rooms[x][y]->getRoomType() == RoomType::NORMAL)
                    cout << rooms[x][y]->getKeyLevel();
                else if (rooms[x][y]->getRoomType() == RoomType::UP)
                    cout << "UU";
                else if (rooms[x][y]->getRoomType() == RoomType::DOWN)
                    cout << "DD";
                else
                    cout << "X";
            }
        }
        cout << endl;
    }
}