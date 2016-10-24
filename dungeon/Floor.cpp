//
// Created by Yorick on 18/10/2016.
//

#include "Floor.h"
#include "../Rng.h"
#include "../DM.h"

using namespace std;

Floor::Floor(bool debug, int amountRooms, Room *prev, int roomsPerLock, bool last) {
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
            Room *firstRoom = new Room(Coordinate(x, y), RoomType::NORMAL);
            addRoom(firstRoom);
            roomCoordinates.push_back(firstRoom->getCoordinate());
            levels[0].push_back(firstRoom->getCoordinate());
            startingRoom = firstRoom;


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
                        validRoom = false;
                        break;
                    }
                }


                if (validRoom) {
                    Room *newRoom = nullptr;

                    if (roomCount() + 1 == _amountRooms) {
                        if (last) {
                            newRoom = new Room(newRoomCoordinate, RoomType::EXIT, keyLevel);
                        } else {
                            newRoom = new Room(newRoomCoordinate, RoomType::DOWN, keyLevel);
                        }
                        stairDown = newRoom;
                    } else {
                        newRoom = new Room(newRoomCoordinate, RoomType::NORMAL, keyLevel);
                    }

                    addRoom(newRoom);
                    if (debug) {
                        newRoom->visit();
                    }

                    roomCoordinates.push_back(newRoom->getCoordinate());
                    levels[keyLevel].push_back(newRoom->getCoordinate());
                    if (roomCount() > 1 && parent) {
                        parent->addDoorTo(newRoom);
                    }
                }
            }

            int extraLinks = (int) (amountRooms * 0.15) + 1;

            for (int l = 0; l < extraLinks; ++l) {
                bool linked = false;
                while (!linked) {
                    int randomX = Rng::getInstance()->randomIntBetween(0, rooms.size() - 1);
                    int randomY = Rng::getInstance()->randomIntBetween(0, rooms[randomX].size() - 1);

                    if (randomX < 0 || randomY < 0 || rooms[randomX][randomY] == nullptr) {
                        continue;
                    }

                    Room *origin = rooms[randomX][randomY];

                    if (origin->getRoomBehindDoor(Direction::NORTH) && origin->getRoomBehindDoor(Direction::EAST) &&
                        origin->getRoomBehindDoor(Direction::SOUTH) && origin->getRoomBehindDoor(Direction::WEST)) {
                        continue;
                    }

                    int dx = 0;
                    int dy = 0;

                    for (int i = 0; i < 10; ++i) {
                        Direction direction;
                        switch (Rng::getInstance()->roleDice(Dice::d4)) {
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
                        if (!origin->getRoomBehindDoor(direction) && rooms[randomX + dx][randomY + dy] != nullptr &&
                            dx != dy) {
                            origin->addDoorTo(rooms[randomX + dx][randomY + dy]);
                            linked = true;
                        }
                    }
                }
            }

            validFloor = true;
        } catch (int e) {
            DM::say("Error: " + to_string(e) + " !!!");
            DM::say("Restarting Generator...");
            for (int x = 0; x < rooms.size(); ++x) {
                for (int y = 0; y < rooms[x].size(); ++y) {
                    delete rooms[x][y];
                }
            }
            rooms.clear();
            roomCoordinates.clear();
            levels.clear();
            startingRoom = nullptr;
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
    while (tries < _amountRooms) {
        signed int rand = Rng::getInstance()->randomIntBetween(0, coordinates.size() - 1);
        Coordinate *coordinate = coordinates.at(rand);

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

//void Floor::drawSurroundings(Coordinate *currentCoordinate, bool debug) {
//    string topBorder = "";
//    string botBorder = "";
//    for (int i = 0; i < 27; ++i) {
//        topBorder += char(220);
//        botBorder += char(223);
//    }
//    cout << topBorder << endl;
//
//    for (int y = currentCoordinate->y - 2; y <= currentCoordinate->y + 2; ++y) {
//        string top = "";
//        string mid = "";
//        string bot = "";
//
//        top += char(219);
//        mid += char(219);
//        bot += char(219);
//
//        for (int x = currentCoordinate->x - 2; x <= currentCoordinate->x + 2; ++x) {
//            Room *currentRoom = rooms[x][y];
//            if (x < 0 || y < 0 || currentRoom == nullptr) {
//                top += "     ";
//                mid += "     ";
//                bot += "     ";
//            } else {
//                if (!currentRoom->visited() && !debug) {
//                    top += "     ";
//                    mid += "     ";
//                    bot += "     ";
//                } else {
//                    bool north = false;
//                    bool east = false;
//                    bool south = false;
//                    bool west = false;
//
//                    if (currentRoom->getRoomBehindDoor(Direction::NORTH)) {
//                        north = true;
//                    }
//                    if (currentRoom->getRoomBehindDoor(Direction::EAST)) {
//                        east = true;
//                    }
//                    if (currentRoom->getRoomBehindDoor(Direction::SOUTH)) {
//                        south = true;
//                    }
//                    if (currentRoom->getRoomBehindDoor(Direction::WEST)) {
//                        west = true;
//                    }
//
//                    if (north) {
//                        top += char(218);
//                        top += char(196);
//                        top += char(193);
//                        top += char(196);
//                        top += char(191);
//                    } else {
//                        top += char(218);
//                        top += char(196);
//                        top += char(196);
//                        top += char(196);
//                        top += char(191);
//                    }
//
//                    if (west) {
//                        mid += char(180);
//                    } else {
//                        mid += char(179);
//                    }
//
//                    if (south) {
//                        bot += char(192);
//                        bot += char(196);
//                        bot += char(194);
//                        bot += char(196);
//                        bot += char(217);
//                    } else {
//                        bot += char(192);
//                        bot += char(196);
//                        bot += char(196);
//                        bot += char(196);
//                        bot += char(217);
//                    }
//
//                    if (currentRoom->getCoordinate()->x == currentCoordinate->x &&
//                        currentRoom->getCoordinate()->y == currentCoordinate->y) {
//                        mid += " @ ";
//                    } else if (currentRoom->getRoomType() == RoomType::NORMAL) {
//                        mid += " " + to_string(currentRoom->getKeyLevel()) + " ";
//                    } else if (currentRoom->getRoomType() == RoomType::DOWN) {
//                        mid += "\\-/";
//                    }
//
//                    if (east) {
//                        mid += char(195);
//                    } else {
//                        mid += char(179);
//                    }
//                }
//            }
//        }
//        cout << top << char(219) << endl;
//        cout << mid << char(219) << endl;
//        cout << bot << char(219) << endl;
//    }
//    cout << botBorder << endl;
//}
//
//void Floor::drawMap(Coordinate *currentCoordinate, bool debug) {
//    string topBorder = "";
//    string botBorder = "";
//    for (int i = 0; i < ((maxX - minX + 3) * 5) + 2; ++i) {
//        topBorder += char(220);
//        botBorder += char(223);
//    }
//    cout << topBorder << endl;
//
//    for (int y = minY - 1; y <= maxY + 1; ++y) {
//        string top = "";
//        string mid = "";
//        string bot = "";
//
//        top += char(219);
//        mid += char(219);
//        bot += char(219);
//
//        for (int x = minX - 1; x <= maxX + 1; ++x) {
//            Room *currentRoom = rooms[x][y];
//            if (x < 0 || y < 0 || currentRoom == nullptr) {
//                top += "     ";
//                mid += "     ";
//                bot += "     ";
//            } else {
//                if (!currentRoom->visited() && !debug) {
//                    top += "     ";
//                    mid += "     ";
//                    bot += "     ";
//                } else {
//                    bool north = false;
//                    bool east = false;//TODO overbodig
//                    bool south = false;
//                    bool west = false;
//
//
//                    if (currentRoom->getRoomBehindDoor(Direction::NORTH)) {
//                        north = true;
//                    }
//                    if (currentRoom->getRoomBehindDoor(Direction::EAST)) {
//                        east = true;
//                    }
//                    if (currentRoom->getRoomBehindDoor(Direction::SOUTH)) {
//                        south = true;
//                    }
//                    if (currentRoom->getRoomBehindDoor(Direction::WEST)) {
//                        west = true;
//                    }
//
//                    if (north) {
//                        top += char(218);
//                        top += char(196);
//                        top += char(193);
//                        top += char(196);
//                        top += char(191);
//                    } else {
//                        top += char(218);
//                        top += char(196);
//                        top += char(196);
//                        top += char(196);
//                        top += char(191);
//                    }
//
//                    if (west) {
//                        mid += char(180);
//                    } else {
//                        mid += char(179);
//                    }
//
//                    if (south) {
//                        bot += char(192);
//                        bot += char(196);
//                        bot += char(194);
//                        bot += char(196);
//                        bot += char(217);
//                    } else {
//                        bot += char(192);
//                        bot += char(196);
//                        bot += char(196);
//                        bot += char(196);
//                        bot += char(217);
//                    }
//
//                    if (currentRoom->getCoordinate()->x == currentCoordinate->x &&
//                        currentRoom->getCoordinate()->y == currentCoordinate->y) {
//                        mid += " @ ";
//                    } else if (currentRoom->getRoomType() == RoomType::NORMAL) {
//                        mid += " " + to_string(currentRoom->getKeyLevel()) + " ";
//                    } else if (currentRoom->getRoomType() == RoomType::DOWN) {
//                        mid += "\\-/";
//                    }
//
//                    if (east) {
//                        mid += char(195);
//                    } else {
//                        mid += char(179);
//                    }
//                }
//            }
//        }
//        cout << top << char(219) << endl;
//        cout << mid << char(219) << endl;
//        cout << bot << char(219) << endl;
//    }
//    cout << botBorder << endl;
//}

Room *Floor::getRoom(int x, int y) {
    return rooms[x][y];
}
