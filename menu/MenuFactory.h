//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_MENUFACTORY_H
#define THE_ELDER_CODES_MENUFACTORY_H


#include "Menu.h"
#include "MenuStart.h"
#include "../enum/GameState.h"
#include "../Game.h"

class MenuFactory {

public:
    MenuFactory() { };
    ~MenuFactory() {};
    static Menu* getMenu(Game * game, GameState state);
};


#endif //THE_ELDER_CODES_MENUFACTORY_H
