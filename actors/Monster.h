//
// Created by Yorick on 20/10/2016.
//

#ifndef THE_ELDER_CODES_MONSTER_H
#define THE_ELDER_CODES_MONSTER_H


#include "Actor.h"

class Monster : public Actor {

protected:
    int _experience;
public:
    Monster(std::string name, int hp, int attack, int defense, int exp);

};


#endif //THE_ELDER_CODES_MONSTER_H
