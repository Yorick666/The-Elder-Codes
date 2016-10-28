//
// Created by Yorick on 26/10/2016.
//

#ifndef THE_ELDER_CODES_CONSUMABLE_H
#define THE_ELDER_CODES_CONSUMABLE_H


#include "Item.h"
#include "../enum/ConsumableType.h"

class Consumable : public Item {
    ConsumableType _type;
    int _diceAmount;
    int _diceSize;
    int _base;

public:
    Consumable(std::string name, int rarity, ConsumableType type, int base, int diceAmount, int diceSize);

    int use(Actor *actor) const;


    const ConsumableType &getConsumableType() const {
        return _type;
    }


    int get_diceAmount() const { return _diceAmount; }

    int get_diceSize() const { return _diceSize; }

    int getBaseValue() const { return _base; }
};


#endif //THE_ELDER_CODES_CONSUMABLE_H
