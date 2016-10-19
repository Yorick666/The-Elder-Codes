//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_GAME_H
#define THE_ELDER_CODES_GAME_H

#include <string>
#include "enum/GameState.h"
#include "Menu.h"
#include "Dungeon.h"
#include "Floor.h"
#include "Room.h"

class Game {
    std::string _input;
    GameState _state;
    Menu *_menu;

    Dungeon *dungeon;
    Floor *currentFloor;
    Room *currentRoom;

public:
    Game();

    ~Game();

    void showScreen();

    GameState getGameState();

    void getInput();
};


#endif //THE_ELDER_CODES_GAME_H
