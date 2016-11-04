//
// Created by Yorick on 20/10/2016.
//

#ifndef THE_ELDER_CODES_MONSTER_H
#define THE_ELDER_CODES_MONSTER_H

#include "Actor.h"

class Monster : public Actor {

protected:
    int _experienceOnKill;
public:
    Monster(std::string name, int experienceOnKill, int hp, int strength, int dexterity, int constitution,
                int proficiencyBonus, int naturalArmor = 10);

    ~Monster() {};

    void addMainAttack(Weapon * weapon);

    void addSecondAttack(Weapon * weapon);

    int getExperienceOnKill() const {return _experienceOnKill;}
};

#endif //THE_ELDER_CODES_MONSTER_H
