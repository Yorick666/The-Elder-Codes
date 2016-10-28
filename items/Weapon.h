//
// Created by Yorick on 20/10/2016.
//

#ifndef THE_ELDER_CODES_WEAPON_H
#define THE_ELDER_CODES_WEAPON_H

#include "../enum/WeaponType.h"
#include "Item.h"
#include <string>

class Weapon : public Item {
    WeaponType _type;
    WeaponType _subType;
    int _diceAmount;
    int _diceSize;

public:
    Weapon(std::string name, int rarity, WeaponType type, int diceAmount, int diceSize , WeaponType subType);

    int use(Actor *actor) const;

    const WeaponType &getWeaponType() const { return _type; };

    int getDiceAmount() const { return _diceAmount; };

    int getDiceSize() const { return _diceSize; };
};


#endif //THE_ELDER_CODES_WEAPON_H
