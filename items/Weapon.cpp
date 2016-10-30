//
// Created by Yorick on 20/10/2016.
//

#include "Weapon.h"
#include "../actors/Actor.h"
#include "../Rng.h"
#include "../DM.h"

Weapon::Weapon(std::string name, int rarity, WeaponType type, int diceAmount, int diceSize, WeaponType subType) : Item(
        name, rarity) {
    _type = type;
    _subType = subType;
    _diceAmount = diceAmount;
    _diceSize = diceSize;
    _itemType = ItemType::WEAPON;
}

int Weapon::use(Actor *actor) const {
    DM::say(actor->getName() + " attacks with " + _name + "!");

    int baseDmg = Rng::roleDice(_diceSize, _diceAmount);

    if (actor->getOffHandWeapon() == this && (actor->getMainWeapon()->getWeaponType() == WeaponType::HEAVY)) {
        DM::say("This should never happen, but if it does: Don't try to cheat!!!");
        return 0;
    }

    if (_type == WeaponType::FINESSE || _subType == WeaponType::FINESSE) {
        return actor->getDexterity() > actor->getStrength() ? baseDmg + actor->getDexterity() : baseDmg +
                                                                                                actor->getStrength();
    } else {
        return baseDmg + actor->getStrength();
    }
}
