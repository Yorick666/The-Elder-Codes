//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_MENU_H
#define THE_ELDER_CODES_MENU_H

#include <string>
#include <vector>
#include "../Game.h"

class Game;

class Menu {

protected:
    std::vector<std::string> _options;
    Game *_game;

    virtual void loadOptions() = 0;

    virtual void getViewScreen() = 0;

public:
    Menu(Game *game);

    ~Menu() {};

    virtual bool handleInput(std::string input) = 0;

    void getMenuScreen();

    virtual void prepareForInput();
};


#endif //THE_ELDER_CODES_MENU_H
