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

    int test = 1;
    int test2 = 0;

    while (!validFloor) {

        try {
            int x = amountRooms / 2;
            int y = amountRooms / 2;

            maxX = x;
            minX = x;
            maxY = y;
            minY = y;
            Room *firstRoom = new Room(Coordinate(x, y), RoomType::UP);
//            cout << "UP with " << firstRoom->getCoordinate()->x << "," << firstRoom->getCoordinate()->y << endl;
            addRoom(firstRoom);
            roomCoordinates.push_back(firstRoom->getCoordinate());
            levels[0].push_back(firstRoom->getCoordinate());
            stairUp = firstRoom;


            int keyLevel = 0; //Number of keys required to get to new room

            // ADDING OTHER ROOMS
            while (roomCount() < amountRooms) {

                bool doLock = false;
                bool validRoom = true;

                if (levels[keyLevel].size() >= roomsPerLock && roomsPerLock > 0) {
                    ++keyLevel;
                    doLock = true;
                }

                Room *parent = nullptr;
                Coordinate newRoomCoordinate;
                while (newRoomCoordinate.x == 0 && newRoomCoordinate.y == 0) {
                    parent = nullptr;
                    if (!doLock && Rng::getInstance()->randomIntBetween(0, 10) > 0 && levels[keyLevel].size() > 0) {
                        parent = getRandomRoomWithFreeEdge(levels[keyLevel]);
                    }
                    if (parent == nullptr) {
                        parent = getRandomRoomWithFreeEdge(roomCoordinates);
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
//                        cout << "ERROR!" << endl;
                        test2++;
                        validRoom = false;
                        break;
                    }
                }


                if (validRoom) {
                    Room *newRoom = nullptr;

                    if (roomCount() + 1 == _amountRooms) {
                        if (last) {
                            newRoom = new Room(newRoomCoordinate, RoomType::EXIT, keyLevel);
//                            cout << "Exit with " << newRoom->getCoordinate()->x << "," << newRoom->getCoordinate()->y <<
//                            endl;
                        } else {
                            newRoom = new Room(newRoomCoordinate, RoomType::DOWN, keyLevel);
//                            cout << "Down with " << newRoom->getCoordinate()->x << "," << newRoom->getCoordinate()->y <<
//                            endl;
                        }
                        stairDown = newRoom;
                    } else {
                        newRoom = new Room(newRoomCoordinate, RoomType::NORMAL, keyLevel);
                    }
                    test++;

                    addRoom(newRoom);
                    roomCoordinates.push_back(newRoom->getCoordinate());
                    levels[keyLevel].push_back(newRoom->getCoordinate());
//                    cout << "Room count: " << roomCount() << endl;
                    if (roomCount() > 1) {
                        linkRooms(parent, newRoom, doLock && keyLevel > 0 ? keyLevel : 0);
                    }

//                parent->addChild(newRoom);
//                cout << roomCount() << endl;
                }
            }
            validFloor = true;
        } catch (int e) {
            cout << e << endl;
            cout << "Restarting Generator...\n\n";
            for (int x = 0; x < rooms.size(); ++x) {
                for (int y = 0; y < rooms[x].size(); ++y) {
                    delete rooms[x][y];
                }
            }
            rooms.clear();
            roomCoordinates.clear();
            levels.clear();
            stairUp = nullptr;
            stairDown = nullptr;
        }

    }
//    cout << "Amount of pushed rooms: " << test << endl;
//    cout << "Amount of Errors: " << test2 << endl;
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
    while (tries < _amountRooms) {
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
    cout << roomCount() << "/" << roomCoordinates.size() << endl;


    for (int y = minY - 2; y <= maxY + 2; ++y) {
        for (int x = minX - 2; x <= maxX + 2; ++x) {
            if (rooms[x][y] == nullptr) {
                cout << ".";
            } else {
                if (rooms[x][y]->getRoomType() == RoomType::NORMAL)
                    cout << rooms[x][y]->getKeyLevel();
                else if (rooms[x][y]->getRoomType() == RoomType::UP)
                    cout << "U";
                else if (rooms[x][y]->getRoomType() == RoomType::DOWN)
                    cout << "D";
                else
                    cout << "X";
            }
        }
        cout << endl;
    }
}