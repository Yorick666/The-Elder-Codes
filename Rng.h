//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_RNG_H
#define THE_ELDER_CODES_RNG_H

#include <random>

// Random Number God
class Rng {
    Rng();

    static Rng *_instance;

    std::mt19937 _gen;

public:
    static Rng *getInstance();

    int roleDice(int amount, int size);

    int randomIntBetween(int min, int max);
};


#endif //THE_ELDER_CODES_RNG_H
