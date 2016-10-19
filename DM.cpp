//
// Created by Yorick on 18/10/2016.
//

#include <time.h>
#include "DM.h"

using namespace std;

DM::DM() {
}

DM *DM::_instance = nullptr;

DM *DM::getInstance() {
    if (!_instance) {
        _instance = new DM();
    }
    return _instance;
}

DM::~DM() {
    delete _instance;
}
