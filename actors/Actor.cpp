//
// Created by Yorick on 18/10/2016.
//

#include "Actor.h"
#include "../enum/Dice.h"
#include "../Rng.h"
#include "../DM.h"

using namespace std;

Actor::Actor(std::string name, int hp, int strength, int dexterity, int constitution, int proficiencyBonus,
             int naturalArmor) {
    _name = name;
    _hp = hp;
    _maxHp = hp;
    _strength = strength;
    _dexterity = dexterity;
    _constitution = constitution;
    _proficiencyBonus = proficiencyBonus;
    _naturalArmor = naturalArmor;
    _mainWeapon = nullptr;
    _offHandWeapon = nullptr;
    _armor = nullptr;
}

void Actor::attack(Actor *target) {
    DM::say("----------" + _name + "----------");
    if (_hp > 0) {
        int dmg = 1 + _strength;
        int hit = Rng::roleDice(Dice::d20) + _proficiencyBonus;

        if (_mainWeapon) {
            dmg = _mainWeapon->use(this);

            if (_mainWeapon->getWeaponType() == WeaponType::FINESSE && _dexterity > _strength) {
                hit += _dexterity;
            } else {
                hit += _strength;
            }
        } else {
            DM::say(_name + " attacks with his/her/its bare fists/claws/hoofs!!!! (whatever you lot have)");
            hit += _strength;
        }

        target->defend(hit, dmg);

        if (_offHandWeapon) {
            dmg = _offHandWeapon->use(this);
            hit = Rng::roleDice(Dice::d20) + _proficiencyBonus;

            if (_offHandWeapon->getWeaponType() == WeaponType::FINESSE && _dexterity > _strength) {
                hit += _dexterity;
            } else {
                hit += _strength;
            }

            target->defend(hit, dmg);
        }
    } else {
        DM::say(_name + " can't attack " + target->getName() + ", because it's dead....");
    }
}

void Actor::defend(int hit, int attack) {
    if (_hp > 0) {
        int AC = 0;

        if (_armor) {
            AC += _armor->use(this);
        } else {
            AC += _naturalArmor + _dexterity;
        }

        if (_offHandWeapon && _offHandWeapon->getWeaponType() == WeaponType::SHIELD) {
            AC += 2;
        }

        if (hit >= AC) {
            DM::say(_name + " is hit! (" + to_string(hit) + " hit roll against " + to_string(AC) +
                    " AC)");
            takeDamage(attack);
        } else {
            int rand = Rng::roleDice(3);
            string miss = "evades";
            if (rand == 1) {
                miss = "blocks";
            } else if (rand == 2) {
                miss = "dodges";
            }
            DM::say(_name + " " + miss + "! (" + to_string(hit) + " hit roll against " + to_string(AC) +
                    " AC)");
        }
    } else {
        DM::say(_name + " is already dead...");
    }
}

void Actor::heal(const int amount) {
    DM::say(getName() + " healed for " + std::to_string(amount) + " hp.");
    if (_hp + amount > _maxHp) {
        _hp = _maxHp;
    } else {
        _hp = _hp + amount;
    }
}

void Actor::takeDamage(int damage) {
    DM::say(_name + " takes " + std::to_string(damage) + " damage!");
    int remainingHp = _hp - damage;
    if (remainingHp < 0) {
        _hp = 0;
        DM::say(_name + " dies!");
    } else {
        _hp = remainingHp;
    }
    int x = 3;
    x = 4;
}

void Actor::addItemToInventory(Item *item) {
    if (_inventory.find(item) == _inventory.end()) {
        _inventory[item] = 1;
    } else {
        _inventory[item] += 1;
    }
}
