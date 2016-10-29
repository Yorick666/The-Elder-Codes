//
// Created by Yorick on 18/10/2016.
//
#include "Player.h"
#include "../DM.h"
#include "../Rng.h"

using namespace std;

Player::Player(Room *currentRoom, string name, int hp, int strength, int dexterity, int constitution,
               int proficiencyBonus,
               int currentSecurityLevel) : Actor(name,
                                                 hp,
                                                 strength,
                                                 dexterity,
                                                 constitution,
                                                 proficiencyBonus) {
    _securityLevel = currentSecurityLevel;
    _currentRoom = currentRoom;
    currentRoom->visit();
}

void Player::travel(Direction direction) {
    if (_currentRoom->hasLivingMonsters()) {
        DM::say("You can't exit the room without <kill>ing all the monsters or you have to try your luck <run>ning away.");
    } else {
        Corridor *c = _currentRoom->getCorridorBehindDoor(direction, _securityLevel);
        if (c) {
            if (!c->isCollapsed()) {
                Room *r = _currentRoom->getRoomBehindDoor(direction, _securityLevel);
                if (r != nullptr) {
                    _currentRoom->clearRoom();
                    _currentRoom = r;
                    _currentRoom->visit();
                }
            } else {
                DM::say("The corridor to the other room is caved in, so you can't travel in that direction.");
            }
        } else {
            DM::say("You can't travel in this direction.");
        }


    }
}

void Player::rest() {
    //TODO
}

void Player::generateStartingGear(std::vector<Item *> *possibleGear) {
    vector<Weapon *> weaponPicker;
    vector<Armor *> armorPicker;
    for (int i = 0; i <= possibleGear->size(); ++i) {
        if (i < possibleGear->size()) {
            Item *item = possibleGear->at(i);
            if (item) {
                if (!_mainWeapon && item->getItemType() == ItemType::WEAPON) {
                    if (item->getRarity() <= 10) {
                        weaponPicker.push_back((Weapon *) item);
                    }
                } else if (!_armor && item->getItemType() == ItemType::ARMOR) {
                    if (item->getRarity() <= 10) {
                        armorPicker.push_back((Armor *) item);
                    }
                } else if (item->getItemType() == ItemType::CONSUMABLE) {
                    if (item->getRarity() <= 10) {
                        addItemToInventory(item);
                        addItemToInventory(item);
                    }
                }
            }
        } else {
            _mainWeapon = weaponPicker[Rng::getRandomIntBetween(0, weaponPicker.size() - 1)];
            _armor = armorPicker[Rng::getRandomIntBetween(0, armorPicker.size() - 1)];
            addItemToInventory(armorPicker[Rng::getRandomIntBetween(0, armorPicker.size() - 1)]);
            addItemToInventory(weaponPicker[Rng::getRandomIntBetween(0, weaponPicker.size() - 1)]);
            addItemToInventory(weaponPicker[Rng::getRandomIntBetween(0, weaponPicker.size() - 1)]);
        }
    }
}

void Player::flee() {
    if (_currentRoom->hasLivingMonsters()) {
        bool found = false;
        while (!found) {
            Direction dir = Rng::getRandomDirection();
            Corridor *c = _currentRoom->getCorridorBehindDoor(dir, _securityLevel);
            if (c && !c->isCollapsed()) {
                Room *r = _currentRoom->getRoomBehindDoor(dir, _securityLevel);
                if (r != nullptr) {
                    _currentRoom->clearRoom();
                    _currentRoom = r;
                    _currentRoom->visit();
                    found = true;
                    DM::say("You succeeded in running away.");
                }
            }
        }
    } else {
        DM::say("Why would you want to flee? There's no danger.");
    }
}

void Player::equip(Item *item) {
    switch (item->getItemType()) {
        case ItemType::ARMOR: {
            Armor *armor = (Armor *) item;
            addItemToInventory(_armor);
            _armor = armor;
            DM::say(_name + " equiped a(n) " + item->getName());
            break;
        }
        case ItemType::WEAPON: {
            Weapon *weapon = (Weapon *) item;
            switch (weapon->getWeaponType()) {
                case WeaponType::SIMPLE:
                    if (!_mainWeapon) {
                        _mainWeapon = weapon;
                        DM::say(_name + " equiped a(n) " + item->getName() + " on his main hand.");
                    } else if (!_offHandWeapon) {
                        _offHandWeapon = weapon;
                        DM::say(_name + " equiped a(n) " + item->getName() + " on his off hand.");
                    } else {
                        DM::say("Do you want to equip this weapon on your <main> or your <off> hand?", true);
                        string input = DM::askInput();
                        if (input == "main" || input == "m") {
                            addItemToInventory(_mainWeapon);
                            _mainWeapon = weapon;
                            DM::say(_name + " equiped a(n) " + item->getName() + " on his main hand.");
                        } else if (input == "off" || input == "o") {
                            if (_mainWeapon->getWeaponType() == WeaponType::HEAVY) {
                                DM::say("You can't wield anything in your off hand when using a heavy weapon.");
                            } else {
                                addItemToInventory(_offHandWeapon);
                                _offHandWeapon = weapon;
                                DM::say(_name + " equiped a(n) " + item->getName() + " on his off hand.");
                            }
                        } else {
                            DM::say("Thank you for using 'You're not taking me serieus' airlines, please never come again!");
                        }
                    }
                    break;
                case WeaponType::FINESSE:
                    if (_mainWeapon) {
                        addItemToInventory(_mainWeapon);
                    }
                    _mainWeapon = weapon;
                    DM::say(_name + " equiped a(n) " + item->getName() + " on his main hand.");
                    break;
                case WeaponType::MARTIAL:
                    if (_mainWeapon) {
                        addItemToInventory(_mainWeapon);
                    }
                    _mainWeapon = weapon;
                    DM::say(_name + " equiped a(n) " + item->getName() + " on his main hand.");
                    break;
                case WeaponType::HEAVY:
                    if (_mainWeapon) {
                        addItemToInventory(_mainWeapon);
                    }
                    _mainWeapon = weapon;
                    DM::say(_name + " equiped a(n) " + item->getName() + " with both hands.");
                    break;
                case WeaponType::SHIELD:
                    if (_offHandWeapon) {
                        addItemToInventory(_offHandWeapon);
                    }
                    _offHandWeapon = weapon;
                    DM::say(_name + " equiped a(n) " + item->getName() + " on his off hand.");
                    break;
            }
            break;
        }
        case ItemType::CONSUMABLE: {
            DM::say("Are you sure that you can equip a(n) " + item->getName() + "?");
            break;
        }
    }

}
