//
// Created by Yorick on 20/10/2016.
//

#ifndef THE_ELDER_CODES_ARMOR_H
#define THE_ELDER_CODES_ARMOR_H

#include "../enum/ArmorType.h"
#include "Item.h"
#include <string>

class Armor : public Item {
    ArmorType _type;
    int _baseAC;
    bool _stealth;
public:
    Armor(std::string name, int rarity, ArmorType type, int baseAC, bool stealth);

    int use(Actor *actor) const;

    int getBaseAC() const { return _baseAC; }

    bool isStealth() const { return _stealth; }
};


#endif //THE_ELDER_CODES_ARMOR_H
