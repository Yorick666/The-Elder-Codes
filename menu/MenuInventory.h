//
// Created by Yorick on 27/10/2016.
//

#ifndef THE_ELDER_CODES_MENUINVENTORY_H
#define THE_ELDER_CODES_MENUINVENTORY_H

#include "Menu.h"
#include "../enum/InventoryState.h"
#include <map>

class Game;

class MenuInventory : public Menu {
    void loadOptions();

    void getViewScreen();

    InventoryState _state;

    std::map<Item *, int> *_inventory;

public:
    MenuInventory(Game *game);

    void handleInput(std::string input);

    void prepareForInput();
};


#endif //THE_ELDER_CODES_MENUINVENTORY_H
