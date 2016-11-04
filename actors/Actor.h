//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_ACTOR_H
#define THE_ELDER_CODES_ACTOR_H

#include <string>
#include <vector>
#include <map>
#include "../items/Weapon.h"
#include "../items/Armor.h"

class Actor {
protected:
    std::string _name;
    int _hp;
    int _maxHp;

protected:
    int _strength;
    int _dexterity;
    int _constitution;
    int _proficiencyBonus;
    int _naturalArmor;
    Weapon *_mainWeapon;
    Weapon *_offHandWeapon;
    Armor *_armor;
    std::map<Item *, int> _inventory;

public:
    Actor(std::string, int hp, int strength, int dexterity, int constitution, int proficiencyBonus,
          int naturalArmor = 10);

    ~Actor() { }

    const std::string getName() const { return _name; }

    int getCurrentHp() const { return _hp; }

    int getMaxHp() const { return _maxHp; }

    int getStrength() const { return _strength; }

    int getDexterity() const { return _dexterity; }

    int getConstitution() const { return _constitution; }

    int getProficiencyBonus() const { return _proficiencyBonus; }

    int getNaturalArmor() const { return _naturalArmor; }

    Weapon *getMainWeapon() const { return _mainWeapon; }

    Weapon *getOffHandWeapon() const { return _offHandWeapon; }

    Armor *getArmor() const { return _armor; }

    std::map<Item *, int> *getInventory() { return &_inventory; }

    virtual void attack(Actor *target);

    virtual void defend(int hit, int attack);

    void heal(const int amount);

    void takeDamage(int damage);

    void addItemToInventory(Item *item);
};


#endif //THE_ELDER_CODES_ACTOR_H
