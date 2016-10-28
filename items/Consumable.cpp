//
// Created by Yorick on 26/10/2016.
//

#include "Consumable.h"
#include "../Rng.h"
#include "../actors/Actor.h"
#include "../DM.h"

Consumable::Consumable(std::string name, int rarity, ConsumableType type, int base, int diceAmount, int diceSize)
        : Item(name, rarity) {
    _itemType = ItemType::CONSUMABLE;
    _type = type;
    _diceAmount = diceAmount;
    _diceSize = diceSize;
    _base = base;
}

int Consumable::use(Actor *actor) const {
    DM::say(actor->getName() + " used a(n) " + _name + ".");

    int amount = _base;
    amount += Rng::roleDice(_diceSize, _diceAmount);

    switch (_type) {
        case ConsumableType::FOOD:
            DM::say("You set up camp, eat some " + _name + " and get a good night rest.");
            actor->heal(amount);
            break;
        case ConsumableType::HEALING:
            actor->heal(amount);
            return amount;
        case ConsumableType::ILLUMINATION:
            break;
        case ConsumableType::BOMB:
            break;
        case ConsumableType::SPELL:
            break;
    }

    return 0;
}
