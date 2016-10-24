//
// Created by Yorick on 24/10/2016.
//

#include <iostream>
#include "DM.h"

using namespace std;

void DM::showMap(Floor *currentFloor, Room *currentRoom, bool debug, bool minimap) {
    int dMaxX = currentFloor->getMaxX() + 1;
    int dMinX = currentFloor->getMinX() - 1;
    int dMaxY = currentFloor->getMaxY() + 1;
    int dMinY = currentFloor->getMinY() - 1;
    int width = (currentFloor->getMaxX() - currentFloor->getMinX() + 3);

    Coordinate *currentCoordinate = currentRoom->getCoordinate();

    if (minimap) {
        dMaxX = currentCoordinate->x + 2;
        dMinX = currentCoordinate->x - 2;
        dMaxY = currentCoordinate->y + 2;
        dMinY = currentCoordinate->y - 2;
        width = 5;
    }

    string topBorder = "";
    string botBorder = "";
    for (int i = 0; i < (width * 5) + 2; ++i) {
        topBorder += char(220);
        botBorder += char(223);
    }
    cout << topBorder << endl;

    for (int y = dMinY; y <= dMaxY; ++y) {
        string top = "";
        string mid = "";
        string bot = "";

        top += char(219);
        mid += char(219);
        bot += char(219);
        for (int x = dMinX; x <= dMaxX; ++x) {
            Room *currentDrawingRoom = currentFloor->getRoom(x, y);
            if (x < 0 || y < 0 || currentDrawingRoom == nullptr) {
                top += "     ";
                mid += "     ";
                bot += "     ";
            } else {
                if (!currentDrawingRoom->visited() && !debug) {
                    top += "     ";
                    mid += "     ";
                    bot += "     ";
                } else {
                    bool north = false;
                    bool east = false;
                    bool south = false;
                    bool west = false;

                    if (currentDrawingRoom->getRoomBehindDoor(Direction::NORTH)) {
                        north = true;
                    }
                    if (currentDrawingRoom->getRoomBehindDoor(Direction::EAST)) {
                        east = true;
                    }
                    if (currentDrawingRoom->getRoomBehindDoor(Direction::SOUTH)) {
                        south = true;
                    }
                    if (currentDrawingRoom->getRoomBehindDoor(Direction::WEST)) {
                        west = true;
                    }

                    if (north) {
                        top += char(218);
                        top += char(196);
                        top += char(193);
                        top += char(196);
                        top += char(191);
                    } else {
                        top += char(218);
                        top += char(196);
                        top += char(196);
                        top += char(196);
                        top += char(191);
                    }

                    if (west) {
                        mid += char(180);
                    } else {
                        mid += char(179);
                    }

                    if (south) {
                        bot += char(192);
                        bot += char(196);
                        bot += char(194);
                        bot += char(196);
                        bot += char(217);
                    } else {
                        bot += char(192);
                        bot += char(196);
                        bot += char(196);
                        bot += char(196);
                        bot += char(217);
                    }

                    if (currentDrawingRoom->getCoordinate()->x == currentCoordinate->x &&
                        currentDrawingRoom->getCoordinate()->y == currentCoordinate->y) {
                        mid += " @ ";
                    } else if (currentDrawingRoom->getRoomType() == RoomType::NORMAL) {
                        mid += " " + to_string(currentDrawingRoom->getKeyLevel()) + " ";
                    } else if (currentDrawingRoom->getRoomType() == RoomType::DOWN) {
                        mid += "\\-/";
                    }

                    if (east) {
                        mid += char(195);
                    } else {
                        mid += char(179);
                    }
                }
            }
        }
        cout << top << char(219) << endl;
        cout << mid << char(219) << endl;
        cout << bot << char(219) << endl;
    }
    cout << botBorder << endl;
}

void DM::say(std::string saying) {
    cout << saying << endl;
}

string DM::askInput() {
    string input;
    cin >> input;
    cout << endl;
    return input;
}
