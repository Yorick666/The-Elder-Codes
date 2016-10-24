//
// Created by Yorick on 20/10/2016.
//

#ifndef THE_ELDER_CODES_ARMOR_H
#define THE_ELDER_CODES_ARMOR_H


#include "Equipment.h"
#include "../enum/ArmorType.h"
#include <string>

class Armor : public Equipment {
    std::string _name;
    ArmorType _type;
    int _baseAC;
    int _maxBaseDefense;
    bool _stealth;
public:
    Armor(std::string name, ArmorType type, int baseAC, int maxBaseDefense, bool stealth = true);


};


#endif //THE_ELDER_CODES_ARMOR_H
