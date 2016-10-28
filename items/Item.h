//
// Created by Yorick on 21/10/2016.
//

#ifndef THE_ELDER_CODES_ITEM_H
#define THE_ELDER_CODES_ITEM_H

#include <string>
#include "../enum/ItemType.h"

class Actor;

class Item {
protected:
    std::string _name;
    int _rarity;
    ItemType _itemType;

public:
    Item(std::string name, int rarity);

    int getRarity() const { return _rarity; };

    const std::string &getName() const { return _name; }

    virtual int use(Actor *actor) const = 0;

    const ItemType &getItemType() const { return _itemType; };
};


#endif //THE_ELDER_CODES_ITEM_H
