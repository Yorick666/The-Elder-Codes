//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_ACTOR_H
#define THE_ELDER_CODES_ACTOR_H

#include <string>
#include "../items/Weapon.h"
#include "../items/Armor.h"

class Actor {
protected:
    std::string _name;
    int _hp;
    int _maxHp;
    int _strength;
    int _dexterity;
    int _constitution;
    int _proficiencyBonus;
    Weapon *_mainWeapon;
    Weapon *_offHandWeapon;
    Armor *_armor;

public:
    Actor(std::string, int hp, int attack, int defense);

    virtual void attack(Actor target);
    virtual void defend(int hit, int attack);
};


#endif //THE_ELDER_CODES_ACTOR_H
