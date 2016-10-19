//
// Created by Yorick on 18/10/2016.
//

#include <iostream>
#include <vector>
#include "Dungeon.h"

using namespace std;

Dungeon::Dungeon(int amountFloors, int roomsPerFloor, int roomsPerLock) {
    floors = vector<Floor>();
    for (int i = 0; i < amountFloors; ++i) {
        if (i == 0) {
            cout << "Generating first floor\n";
            Floor newFloor = Floor(roomsPerFloor, nullptr, roomsPerLock);
            floors.push_back(newFloor);
            currentFloor = &floors[0];
            currentRoom = currentFloor->getStairsUp();
        }
        else if (i == amountFloors - 1) {
            cout << "Generating last floor\n";
            Floor newFloor = Floor(roomsPerFloor, floors.at(i - 1).getStairsDown(), roomsPerLock, true);
            floors.push_back(newFloor);
        }
        else {
            cout << "Generating floor " << i + 1 << "\n";
            Floor newFloor = Floor(roomsPerFloor, floors.at(i - 1).getStairsDown(), roomsPerLock);
            floors.push_back(newFloor);
        }
        floors[i].drawFloor();
    }
    cout << "Finished\n";
}

Floor *Dungeon::getCurrentFloor() {
    return nullptr;
}

Room *Dungeon::getCurrentRoom() {
    return nullptr;
}
