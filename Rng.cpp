//
// Created by Yorick on 18/10/2016.
//

#include <time.h>
#include <random>
#include "Rng.h"

using namespace std;

Rng * Rng::_instance = nullptr;

Rng::Rng() {
    _gen = mt19937(time(NULL));
}

Rng *Rng::getInstance() {
    if (!_instance)
        _instance = new Rng();
    return _instance;
}

int Rng::roleDice(int amount, int size) {


    uniform_int_distribution<> dis(1, size);
    int result = 0;
    for (int i = 0; i < amount; ++i) {
        result += dis(_gen);
    }

    return result;
}

int Rng::randomIntBetween(int min, int max) {
    if (min < max) {
        uniform_int_distribution<> dis(min, max);
        return dis(_gen);
    }
    return 0;
}
