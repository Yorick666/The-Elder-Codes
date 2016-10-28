//
// Created by Yorick on 20/10/2016.
//

#include "Armor.h"
#include "../actors/Actor.h"

using namespace std;

Armor::Armor(string name, int rarity, ArmorType type, int baseAC, bool stealth) : Item(name, rarity) {
    _type = type;
    _baseAC = baseAC;
    _stealth = stealth;
    _itemType = ItemType::ARMOR;
}

int Armor::use(Actor *actor) const {
    int shield = 0;

    if (actor->getOffHandWeapon() && actor->getOffHandWeapon()->getWeaponType() == WeaponType::SHIELD) {
        shield = 2;
    }

    switch (_type) {
        case ArmorType::LIGHT:
            return _baseAC + actor->getDexterity() + shield;
        case ArmorType::MEDIUM:
            return actor->getDexterity() > 2 ? _baseAC + 2 + shield : _baseAC + actor->getDexterity() + shield;
        case ArmorType::HEAVY:
            return _baseAC + shield;
    }
}
