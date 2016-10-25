//
// Created by Yorick on 18/10/2016.
//

#include <vector>
#include <iomanip>
#include "Dungeon.h"
#include "../DM.h"

using namespace std;

Dungeon::Dungeon(bool debug, int amountFloors, int roomsPerFloor, int roomsPerLock) {
    floors = vector<Floor*>();

    currentLevel = 0;

    for (int i = 0; i < amountFloors; ++i) {
        DM::say("Generating Floor - " + to_string(i + 1) + "/" + to_string(amountFloors), true);
        Floor * newFloor = nullptr;
        if (i == 0) {
            newFloor = new Floor(debug, roomsPerFloor, roomsPerLock);
        }
        else if (i == amountFloors - 1) {
            newFloor = new Floor(debug, roomsPerFloor, roomsPerLock, true);
        }
        else {
            newFloor = new Floor(debug, roomsPerFloor, roomsPerLock);
        }
        floors.push_back(newFloor);
    }
    DM::say("Generating dungeon - Finished", true);
}

Room *Dungeon::descend() {
    if (floors.size() == currentLevel) {
        return nullptr; //TODO ending a game
    } else {
        currentLevel++;
        return getStartingRoom();
    }
}

Dungeon::~Dungeon() {
    for (int i = 0; i < floors.size(); ++i) {
        if (floors[i]){
            delete floors[i];
        }
    }
}
