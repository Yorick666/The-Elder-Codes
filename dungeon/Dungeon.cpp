//
// Created by Yorick on 18/10/2016.
//

#include <vector>
#include <iomanip>
#include "Dungeon.h"
#include "../DM.h"

using namespace std;

Dungeon::Dungeon(bool debug, int amountFloors, int roomsPerFloor, int roomsPerLock) {
    floors = vector<Floor>();

    for (int i = 0; i < amountFloors; ++i) {
        DM::say("Generating Floor - " + to_string(i + 1) + "/" + to_string(amountFloors));
        if (i == 0) {
            Floor newFloor = Floor(debug, roomsPerFloor, nullptr, roomsPerLock);
            floors.push_back(newFloor);
        }
        else if (i == amountFloors - 1) {
            Floor newFloor = Floor(debug, roomsPerFloor, floors.at(i - 1).getStairsDown(), roomsPerLock, true);
            floors.push_back(newFloor);
        }
        else {
            Floor newFloor = Floor(debug, roomsPerFloor, floors.at(i - 1).getStairsDown(), roomsPerLock);
            floors.push_back(newFloor);
        }
    }
    _currentFloor = &floors[0];
    _currentRoom = _currentFloor->getStartingRoom();
    _currentRoom->visit();
    DM::say("Generating dungeon - Finished");
}

Floor *Dungeon::getCurrentFloor() {
    return _currentFloor;
}

Room *Dungeon::getCurrentRoom() {
    return _currentRoom;
}

void Dungeon::drawSurroundings(bool debug) {
    DM::showMap(_currentFloor, _currentRoom, debug, true);
}

void Dungeon::drawMap(bool debug) {
    DM::showMap(_currentFloor, _currentRoom, debug);
}

void Dungeon::travel(Direction direction, int keyLevel) {
    Link *l = _currentRoom->getLink(direction);
    if (l != nullptr) {
        Room *target = l->travel(_currentRoom, keyLevel);

        if (target != nullptr) {
            _currentRoom = target;
            _currentRoom->visit();
        } else {
            DM::say("You have to find a higher level key. \nYou have a lvl " + to_string(keyLevel) +
                    " key, but you need the level " +
                    to_string(l->getKeyLevel()) + " key.");
        }
    } else {
        DM::say("There is no exit in this direction.");
    }
}
