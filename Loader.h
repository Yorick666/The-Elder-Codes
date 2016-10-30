//
// Created by Yorick on 26/10/2016.
//

#ifndef THE_ELDER_CODES_LOADER_H
#define THE_ELDER_CODES_LOADER_H

#include <vector>
#include "items/Item.h"
#include "actors/Monster.h"
#include "actors/Player.h"

class Loader {
public:
    static std::vector<Item *> loadItems();

    static std::map<Monster *, std::vector<Weapon *>> loadMonsters();

    static Player *loadPlayer();

    static void savePlayer(Player *player);
};


#endif //THE_ELDER_CODES_LOADER_H
