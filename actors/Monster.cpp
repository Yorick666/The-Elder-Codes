//
// Created by Yorick on 20/10/2016.
//

#include "Monster.h"

Monster::Monster(std::string name, int hp, int attack, int defense, int exp) : Actor(name, hp, attack, defense) {
    _experience = exp;
}
