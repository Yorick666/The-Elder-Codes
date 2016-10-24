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

    currentLevel = 0;

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
    DM::say("Generating _dungeon - Finished");
}

Room *Dungeon::descend() {
    if (floors.size() == currentLevel) {
        return nullptr; //TODO ending a game
    } else {
        currentLevel++;
        return getStartingRoom();
    }
}
