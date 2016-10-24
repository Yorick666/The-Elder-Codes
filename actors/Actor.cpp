//
// Created by Yorick on 18/10/2016.
//

#include "Actor.h"

Actor::Actor(std::string name, int hp, int attack, int defense) {
    _name = name;
    _hp = hp;
    _maxHp = hp;
    _baseAttack = attack;
    _baseDefense = defense;
}
