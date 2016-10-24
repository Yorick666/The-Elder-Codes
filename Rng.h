//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_RNG_H
#define THE_ELDER_CODES_RNG_H

#include <random>
#include "enum/Dice.h"

// Random Number God
class Rng {
    Rng();

    static Rng *_instance;

    std::mt19937 _gen;

public:
    static Rng *getInstance();

    signed int roleDice(int size, signed int amount = 1);
    signed int roleDice(Dice dice, signed int amount = 1);

    signed int randomIntBetween(signed int min,signed int max);
};


#endif //THE_ELDER_CODES_RNG_H
