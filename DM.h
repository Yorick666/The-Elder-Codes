//
// Created by Yorick on 24/10/2016.
//

#ifndef THE_ELDER_CODES_DM_H
#define THE_ELDER_CODES_DM_H

#include "dungeon/Floor.h"
#include <string>
#include <queue>

class DM {
    DM() { };

    static DM *_instance;

    std::queue<std::string> _outputQueue;

public:
    static DM *getInstance();

    static void showMap(Floor *currentFloor, Room *currentRoom, bool debug, int securityLevel, bool minimap = false);

    static void say(std::string saying, bool direct = false);

    void showOutput();

    void addLineToQueue(std::string line);

    static std::string askInput();
};


#endif //THE_ELDER_CODES_DM_H
