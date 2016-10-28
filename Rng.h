//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_RNG_H
#define THE_ELDER_CODES_RNG_H

#include <random>
#include "enum/Dice.h"
#include "enum/Direction.h"

// Random Number God
class Rng {
    Rng();

    static Rng *_instance;

    std::mt19937 _gen;

    static Rng *getInstance();

public:

    static signed int roleDice(int size, signed int amount = 1);

    static signed int roleDice(Dice dice, signed int amount = 1);

    static signed int getRandomIntBetween(signed int min, signed int max);

    static Direction getRandomDirection();
};


#endif //THE_ELDER_CODES_RNG_H
