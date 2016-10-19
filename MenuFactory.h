//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_MENUFACTORY_H
#define THE_ELDER_CODES_MENUFACTORY_H


#include "Menu.h"
#include "MenuStart.h"
#include "enum/GameState.h"

class MenuFactory {
    MenuFactory() { };
    static MenuFactory *_instance;

public:
    ~MenuFactory() {};
    static MenuFactory * getInstance();
    Menu* getMenu(GameState state);
};


#endif //THE_ELDER_CODES_MENUFACTORY_H
