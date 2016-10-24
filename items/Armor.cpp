//
// Created by Yorick on 20/10/2016.
//

#include "Armor.h"

using namespace std;

Armor::Armor(string name, ArmorType type, int baseAC, int maxBaseDefense, bool stealth) : Equipment() {
    _name = name;
    _type = type;
    _baseAC = baseAC;
    _maxBaseDefense = maxBaseDefense;
    _stealth = stealth;
}
