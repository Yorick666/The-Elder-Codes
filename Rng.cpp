//
// Created by Yorick on 18/10/2016.
//

#include <time.h>
#include <random>
#include "Rng.h"

using namespace std;

Rng *Rng::_instance = nullptr;

Rng::Rng() {
    _gen = mt19937(time(NULL));
}

Rng *Rng::getInstance() {
    if (!_instance)
        _instance = new Rng();
    return _instance;
}

signed int Rng::roleDice(signed int size, signed int amount) {
    uniform_int_distribution<> dis(1, size);
    signed int result = 0;
    for (int i = 0; i < amount; ++i) {
        result += dis(_gen);
    }

    return result;
}

signed int Rng::roleDice(Dice dice, signed int amount) {
    uniform_int_distribution<> dis(1, (signed int) dice);
    signed int result = 0;
    for (int i = 0; i < amount; ++i) {
        result += dis(_gen);
    }

    return result;
}

signed int Rng::randomIntBetween(signed int min, signed int max) {
    if (min < max) {
        uniform_int_distribution<> dis(min, max);
        return dis(_gen);
    }
    return 0;
}
