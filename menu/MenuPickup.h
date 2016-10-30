//
// Created by Yorick on 30/10/2016.
//

#ifndef THE_ELDER_CODES_MENUPICKUP_H
#define THE_ELDER_CODES_MENUPICKUP_H

#include "Menu.h"

class Game;

class MenuPickup : public Menu{
    void loadOptions();

    void getViewScreen();

public:
    MenuPickup(Game *game);

    void handleInput(std::string input);
};


#endif //THE_ELDER_CODES_MENUPICKUP_H
