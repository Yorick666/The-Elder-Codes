//
// Created by Yorick on 18/10/2016.
//

#include "Actor.h"
#include "../enum/Dice.h"
#include "../Rng.h"

Actor::Actor(std::string name, int hp, int attack, int defense) {
    _name = name;
    _hp = hp;
    _maxHp = hp;
    _baseAttack = attack;
    _baseDefense = defense;
    _mainWeapon = nullptr;
    _offHandWeapon = nullptr;
    _armor = nullptr;
}

void Actor::attack(Actor target) {
    int hit = Rng::getInstance()->roleDice(Dice::d20) + _baseAttack;
    int dmg = 0;

    if (_mainWeapon) {
        dmg += _mainWeapon->use() + _baseAttack;
    }

    if (_offHandWeapon){
        dmg += _offHandWeapon->use() + _baseAttack;
    }

    target.defend(hit, dmg);
}

void Actor::defend(int hit, int attack) { //TODO defense and stuff
    int AC = _baseDefense;

    if (_armor) {
        AC += _armor->use();
    }

    if (hit >= AC) {
        int remainingHp = _hp - attack;
        if (remainingHp <0) {
            _hp = 0;
        } else {
            _hp = remainingHp;
        }
    } else {
        //Mis
    }
}
