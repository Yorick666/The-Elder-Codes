//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_GAME_H
#define THE_ELDER_CODES_GAME_H

#include <string>
#include "enum/GameState.h"
#include "dungeon/Dungeon.h"
#include "actors/Player.h"

class Menu;

class Game {
    std::vector<Item *> _items;
    std::map<Monster *, std::vector<Weapon *>> _monsters;
    std::string _input;
    GameState _state;
    Menu *_menu;

    Dungeon *_dungeon;

    Player *_player;

    bool debugMode;

public:
    Game();

    ~Game();

    void showScreen();

    GameState getGameState();

    void getInput();

    void changeState(GameState newState);

    void startNewGame(std::string playerName, bool debug = false, int size = 2, int roomsPerFloor = 10,
                      int roomsPerLock = 0);

    Player *getPlayer() { return _player; };

    bool isDebug() { return debugMode; };

    Room *getCurrentRoom() { return _player->getCurrentRoom(); };

    Floor *getCurrentFloor() { return _dungeon->getCurrentFloor(); };

    void generateMonsters(Room *room);

    void flee();

    void monsterCombat();

    void readyRoom(Direction direction = Direction::NORTH);

    void checkDeadMonsters();

    std::vector<Item *> generateLoot(int monsterExp);

    void loadPlayer();

    void savePlayer();

    void resetPlayer();

    void showHelpScreen();
};


#endif //THE_ELDER_CODES_GAME_H
