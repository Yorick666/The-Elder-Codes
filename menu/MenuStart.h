//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_MENUSTART_H
#define THE_ELDER_CODES_MENUSTART_H

#include "Menu.h"

class Game;

class MenuStart : public Menu {

    void loadOptions();

    void getViewScreen();

public:
    MenuStart(Game *game);

    ~MenuStart() { };

    void handleInput(std::string input);
};


#endif //THE_ELDER_CODES_MENUSTART_H
