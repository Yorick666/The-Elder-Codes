//
// Created by Yorick on 26/10/2016.
//

#ifndef THE_ELDER_CODES_LOADER_H
#define THE_ELDER_CODES_LOADER_H

#include <vector>
#include "items/Item.h"

class Loader {
public:
    static std::vector<Item *> loadItems();
};


#endif //THE_ELDER_CODES_LOADER_H
