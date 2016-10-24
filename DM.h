//
// Created by Yorick on 24/10/2016.
//

#ifndef THE_ELDER_CODES_DM_H
#define THE_ELDER_CODES_DM_H


#include "dungeon/Floor.h"
#include <string>

class DM {

public:
    static void showMap(Floor *currentFloor, Room *currentRoom, bool debug, bool minimap = false);

    static void say(std::string saying);

    static std::string askInput();
};


#endif //THE_ELDER_CODES_DM_H
