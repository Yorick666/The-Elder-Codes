#include "Player.h"
#include "../DM.h"
#include "../Rng.h"

using namespace std;

Player::Player(Room *currentRoom, string name, int hp, int strength, int dexterity, int constitution,
               int proficiencyBonus, int level, int experience) : Actor(name,
                                                                        hp,
                                                                        strength,
                                                                        dexterity,
                                                                        constitution,
                                                                        proficiencyBonus) {
    _securityLevel = 0;
    _currentRoom = currentRoom;
    if (level < 1) {
        level = 1;
    }
    _level = level;
    _experience = experience;
    if (currentRoom) {
        currentRoom->visit();
    }
}

Player::Player(Room *currentRoom, Player *loadedPlayer) : Actor(loadedPlayer->getName(),
                                                                loadedPlayer->getMaxHp(),
                                                                loadedPlayer->getStrength(),
                                                                loadedPlayer->getDexterity(),
                                                                loadedPlayer->getConstitution(),
                                                                loadedPlayer->getProficiencyBonus()) {
    _level = loadedPlayer->getLevel();
    _experience = loadedPlayer->getExperience();
    _mainWeapon = loadedPlayer->getMainWeapon();
    _offHandWeapon = loadedPlayer->getOffHandWeapon();
    _armor = loadedPlayer->getArmor();
    _securityLevel = 0;
    _currentRoom = currentRoom;
    _currentRoom->visit();
}

bool Player::travel(Direction direction) {
    if (_currentRoom->hasLivingMonsters()) {
        DM::say("You can't exit the room without <kill>ing all the monsters or you have to try your luck <run>ning away.");
    } else {
        Corridor *c = _currentRoom->getCorridorBehindDoor(direction);
        if (c) {
            c = _currentRoom->getCorridorBehindDoor(direction, _securityLevel);
            if (c){
                if (!c->isCollapsed()) {
                    Room *r = _currentRoom->getRoomBehindDoor(direction, _securityLevel);
                    if (r != nullptr) {
                        _currentRoom->clearRoom();
                        _currentRoom = r;
                        return true;
                    }
                } else {
                    DM::say("The entrance to the other room is caved in, so you can't travel in that direction.");
                }
            } else {
                DM::say("Your security level is not high enough. Try to find the plot device hidden somewhere in the dungeon.");
            }
        } else {
            DM::say("You can't travel in this direction.");
        }
    }
    return false;
}

void Player::flee() {
    while (true) {
        Direction dir = Rng::getRandomDirection();
        Corridor *c = _currentRoom->getCorridorBehindDoor(dir, _securityLevel);
        if (c && !c->isCollapsed()) {
            Room *r = _currentRoom->getRoomBehindDoor(dir, _securityLevel);
            if (r != nullptr) {
                _currentRoom->clearRoom();
                _currentRoom = r;
                DM::say("You succeeded in running away.");
                break;
            }
        }
    }
}

void Player::equip(const Item *item) {
    if (item) {
        switch (item->getItemType()) {
            case ItemType::ARMOR: {
                Armor *armor = (Armor *) item;
                if (_armor) {
                    addItemToInventory(_armor);
                }
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
                            DM::say("Do you want to equip this weapon on your <m/main> or your <o/off> hand?", true);
                            string input = DM::askInput();
                            if (input == "main" || input == "m") {
                                if (_mainWeapon) {
                                    addItemToInventory(_mainWeapon);
                                }
                                _mainWeapon = weapon;
                                DM::say(_name + " equiped a(n) " + item->getName() + " on his main hand.");
                            } else if (input == "off" || input == "o") {
                                if (_mainWeapon->getWeaponType() == WeaponType::HEAVY) {
                                    DM::say("You can't wield anything in your off hand when using a heavy weapon.");
                                } else {
                                    if (_offHandWeapon) {
                                        addItemToInventory(_offHandWeapon);
                                    }
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

                        if (_offHandWeapon) {
                            addItemToInventory(_offHandWeapon);
                            _offHandWeapon = nullptr;
                        }

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
}

void Player::gainExperience(const int exp) {
    _experience += exp;
}

void Player::checkForLevelUp() {
    int neededExp = pow(3, _level) * 100;
    if (_experience >= neededExp) {
        _experience -= neededExp;
        _level++;
        DM::say("Level " + to_string(_level) + " reached!\n");
        DM::say("<s/strength>: Adds damage and chance to hit to weapons.", true);
        DM::say("<d/dexterity>: Adds damage/hit chance to finesse weapons and increases AC with the right armor.",
                true);
        DM::say("<c/constitution>: Adds 1 guaranteed hp per level (starting with this one).", true);
        while (true) {
            DM::say("What stat do you want to increase?", true);
            string input = DM::askInput();
            if (input == "s" || input == "strength") {
                _strength++;
            } else if (input == "d" || input == "dexterity") {
                _dexterity++;
            } else if (input == "c" || input == "constitution") {
                _constitution++;
            } else {
                continue;
            }
            break;
        }
        _maxHp += Rng::roleDice(10) + _constitution;
        _hp = _maxHp;

        if (_level % 4 == 0) {
            _proficiencyBonus++;
        }
    }
}

void Player::unequip(Item *item) {
    if (item) {
        if (item == _mainWeapon) {
            DM::say(_name + " unequips " + item->getName());
            addItemToInventory(_mainWeapon);
            _mainWeapon = nullptr;
        } else if (item == _offHandWeapon) {
            DM::say(_name + " unequips " + item->getName());
            addItemToInventory(_offHandWeapon);
            _offHandWeapon = nullptr;
        } else if (item == _armor) {
            DM::say(_name + " unequips " + item->getName());
            addItemToInventory(_armor);
            _armor = nullptr;
        } else {
            DM::say("Yes.... take off what you don't even have equiped.");
        }
    } else {
        DM::say("You don't even have anything equiped....");
    }
}

void Player::upgradeSecurityLevel() {
    _securityLevel++;
    DM::say("For some reason you feel your security level increasing. Prais Deus ex machina!!!");
}
