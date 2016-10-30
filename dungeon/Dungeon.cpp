//
// Created by Yorick on 18/10/2016.
//

#include <vector>
#include <iomanip>
#include "Dungeon.h"
#include "../DM.h"

using namespace std;

Dungeon::Dungeon(bool debug, int amountFloors, int roomsPerFloor, int roomsPerLock) {
    _floors = vector<Floor *>();

    _currentLevel = 0;

    for (int i = 0; i < amountFloors; ++i) {
        DM::say("Generating Floor - " + to_string(i + 1) + "/" + to_string(amountFloors), true);
        Floor *newFloor = nullptr;
        if (i == 0) {
            newFloor = new Floor(debug, nullptr, roomsPerFloor, roomsPerLock);
        }
        else if (i == amountFloors - 1) {
            Room *previous = _floors[i - 1]->getExitRoom();
            newFloor = new Floor(debug, previous, roomsPerFloor, roomsPerLock, true);
            _stairs.push_back(new Corridor(previous, newFloor->getStartingRoom(),true));
        }
        else {
            Room *previous = _floors[i - 1]->getExitRoom();
            newFloor = new Floor(debug, previous, roomsPerFloor, roomsPerLock);
            _stairs.push_back(new Corridor(previous, newFloor->getStartingRoom(),true));
        }
        _floors.push_back(newFloor);
    }
    DM::say("Generating dungeon - Finished", true);
}

Room *Dungeon::descend() {
    if (_floors.size() == _currentLevel) {
        return nullptr;
    } else {
        _currentLevel++;
        return getStartingRoom();
    }
}

Room *Dungeon::ascend() {
    if (_currentLevel > 0) {
        _currentLevel--;
        return getExitRoom();
    } else {
        return nullptr;
    }
}

Dungeon::~Dungeon() {
    for (Floor *floor : _floors) {
        if (floor) {
            delete floor;
        }
    }

    for (Corridor *corridor: _stairs) {
        if (corridor) {
            delete corridor;
        }
    }
}
