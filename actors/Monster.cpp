//
// Created by Yorick on 20/10/2016.
//

#include "Monster.h"

Monster::Monster(std::string name, int experienceOnKill, int hp, int strength, int dexterity, int constitution,
            int proficiencyBonus, int naturalArmor) : Actor(name, hp, strength, dexterity,constitution,proficiencyBonus) {
    _experienceOnKill = experienceOnKill;
    _naturalArmor = naturalArmor;
}
