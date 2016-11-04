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

    switch (_type) {
        case ArmorType::LIGHT:
            return _baseAC + actor->getDexterity();
        case ArmorType::MEDIUM:
            return actor->getDexterity() > 2 ? _baseAC + 2 : _baseAC + actor->getDexterity();
        case ArmorType::HEAVY:
            return _baseAC;
    }
}

int Armor::getMaxDex(const int dex) const {
    switch (_type) {
        case ArmorType::LIGHT:
            return dex;
        case ArmorType::MEDIUM:
            if (dex < 2) {
                return dex;
            }
            return 2;
        case ArmorType::HEAVY:
            return 0;
    }
}
