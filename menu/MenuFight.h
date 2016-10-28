//
// Created by Yorick on 27/10/2016.
//

#ifndef THE_ELDER_CODES_MENUFIGHT_H
#define THE_ELDER_CODES_MENUFIGHT_H


#include "Menu.h"

class Game;

class MenuFight : public Menu {
    void loadOptions();

    void getViewScreen();

public:
    MenuFight(Game *game);

    void handleInput(std::string input);

    void prepareForInput();
};


#endif //THE_ELDER_CODES_MENUFIGHT_H
