//
// Created by Yorick on 27/10/2016.
//

#include "MenuInventory.h"
#include "../DM.h"
#include "../items/Consumable.h"
#include <regex>
#include <iostream>

using namespace std;

MenuInventory::MenuInventory(Game *game) : Menu(game) {
    _state = InventoryState::STANDBY;
    _inventory = game->getPlayer()->getInventory();
}


void MenuInventory::loadOptions() {
    _options.push_back("equip [id]");
    _options.push_back("use [id]");
    _options.push_back("drop [id]");
    _options.push_back("back");
}

void MenuInventory::getViewScreen() {
    DM::say("Gear:");
    Player *player = _game->getPlayer();
    Weapon *main = player->getMainWeapon();
    if (main) {
        int base = player->getStrength();
        string type = "";
        switch (main->getWeaponType()) {
            case WeaponType::SIMPLE:
                type = "Simple Weapon";
                break;
            case WeaponType::FINESSE:
                if (player->getDexterity() > player->getStrength()) {
                    base = player->getDexterity();
                }
                type = "Finesse Weapon";
                break;
            case WeaponType::MARTIAL:
                type = "Martial Weapon";
                break;
            case WeaponType::HEAVY:
                type = "heavy Weapon";
                break;
            case WeaponType::SHIELD:
                type = "Shield";
                break;
        }

        DM::say("\t<Main> Weapon: " + main->getName() + " (" + to_string(main->getDiceAmount()) + "d" +
                to_string(main->getDiceSize()) + "+" + to_string(base) + " " + type + ")");
    } else {
        DM::say("\t<Main> Weapon: None");
    }

    Weapon *off = player->getOffHandWeapon();
    if (off) {
        int base = player->getStrength();
        string type = "";
        switch (off->getWeaponType()) {
            case WeaponType::SIMPLE:
                type = "Simple Weapon";
                break;
            case WeaponType::FINESSE:
                if (player->getDexterity() > player->getStrength()) {
                    base = player->getDexterity();
                }
                type = "Finesse Weapon";
                break;
            case WeaponType::MARTIAL:
                type = "Martial Weapon";
                break;
            case WeaponType::HEAVY:
                type = "heavy Weapon";
                break;
            case WeaponType::SHIELD:
                type = "Shield";
                break;
        }

        DM::say("\t<Off>hand Weapon: " + off->getName() + " (" + to_string(off->getDiceAmount()) + "d" +
                to_string(off->getDiceSize()) + "+" + to_string(base) + " " + type + ")");
    } else {
        DM::say("\t<Off>hand Weapon: None");
    }

    Armor *armor = player->getArmor();
    if (armor) {
        DM::say("\t<Armor>: " + armor->getName() + " (" + to_string(armor->getBaseAC()) + " AC)");
    } else {
        DM::say("\t<Armor>: None");
    }

//    map<Item *, int> *inventory = player->getInventory();
//    for (auto const &item : inventory) { }

    DM::say("\nInventory:");
    int i = 1;
    for (map<Item *, int>::iterator item = _inventory->begin(); item != _inventory->end(); ++item) {
        switch (item->first->getItemType()) {
            case ItemType::ARMOR: {
                Armor *armor = (Armor *) item->first;
                DM::say("\t<" + to_string(i) + ">: " + item->first->getName() + " - " + to_string(armor->getBaseAC()) +
                        " AC (" + to_string(item->second) + "x)");
                break;
            }
            case ItemType::WEAPON: {
                Weapon *weapon = (Weapon *) item->first;

                string type = "";
                switch (weapon->getWeaponType()) {
                    case WeaponType::SIMPLE:
                        type = "Simple Weapon";
                        break;
                    case WeaponType::FINESSE:
                        type = "Finesse Weapon";
                        break;
                    case WeaponType::MARTIAL:
                        type = "Martial Weapon";
                        break;
                    case WeaponType::HEAVY:
                        type = "heavy Weapon";
                        break;
                    case WeaponType::SHIELD:
                        type = "Shield";
                        break;
                }

                DM::say("\t<" + to_string(i) + ">: " + item->first->getName() + " - " + type + " - " +
                        to_string(weapon->getDiceAmount()) +
                        "d" + to_string(weapon->getDiceSize()) + " dmg (" + to_string(item->second) + "x)");
                break;
            }
            case ItemType::CONSUMABLE: {
                Consumable *consumable = (Consumable *) item->first;

                string type = "";
                string effect = "";

                switch (consumable->getConsumableType()) {
                    case ConsumableType::FOOD:
                        type = "Food";
                        effect = "hp";
                        break;
                    case ConsumableType::HEALING:
                        type = "Healing item";
                        effect = "hp";
                        break;
                    case ConsumableType::ILLUMINATION:
                        type = "Illumination";
                        effect = "room(s) of light";
                        break;
                    case ConsumableType::BOMB:
                        type = "Bomb";
                        if (consumable->getDiceAmount() == 0) {
                            effect = "cave-in(s)";
                        } else {
                            effect = "probable cave-in(s)";
                        }
                        break;
                    case ConsumableType::TALISMAN:
                        type = "Talisman";
                        effect = "maximum distance to exit";
                        break;
                }

                if (consumable->getDiceAmount() == 0) {
                    DM::say("\t<" + to_string(i) + ">: " + consumable->getName() + " - " + type + " - " +
                            to_string(consumable->getBaseValue()) + " " + effect + " (" +
                            to_string(item->second) + "x)");
                } else {
                    DM::say("\t<" + to_string(i) + ">: " + consumable->getName() + " - " + type + " - " +
                            to_string(consumable->getDiceAmount()) + "d" + to_string(consumable->getDiceSize()) +
                            "+" +
                            to_string(consumable->getBaseValue()) + " " + effect + " (" +
                            to_string(item->second) + "x)");
                }
                break;
            }
        }
        ++i;
    }
    if (i == 1) {
        DM::say("\tNo items");
    }
}

void MenuInventory::handleInput(std::string input) {
    if (regex_match(input, regex("b|back"))) {
        _game->changeState(GameState::ROAMING);
    } else if (regex_match(input, regex("(e|equip)"))) {
        _state = InventoryState::EQUIP;
    } else if (regex_match(input, regex("(d|drop)"))) {
        _state = InventoryState::DROP;
    } else if (regex_match(input, regex("(u|use)"))) {
        _state = InventoryState::USE;
    } else if (_state != InventoryState::STANDBY && regex_match(input, regex("^\\d+$"))) {
        int x = stoi(input);
        int i = 1;
        for (map<Item *, int>::iterator item = _inventory->begin(); item != _inventory->end(); item++) {
            bool done = false;
            if (x == i) {
                done = true;
                if (item->second > 0) {
                    switch (_state) {
                        case InventoryState::STANDBY:
                            DM::say("You want to put WHAT WHERE?!?!");
                            break;
                        case InventoryState::EQUIP:
                            if (item->first->getItemType() != ItemType::CONSUMABLE) {
                                Player *player = _game->getPlayer();
                                player->equip(item->first);
                                item->second -= 1;
                                if (item->second == 0) {
                                    _inventory->erase(item->first);
                                }
                            } else {
                                DM::say("You want to put WHAT WHERE?!?!");
                            }
                            break;
                        case InventoryState::USE:
                            if (item->first->getItemType() == ItemType::CONSUMABLE) {
                                Consumable *consumable = (Consumable *) item->first;
                                if (consumable->getConsumableType() == ConsumableType::BOMB) {
                                    if (_game->getCurrentRoom()->hasLivingMonsters()) {
                                        if (consumable->explode(_game->getCurrentFloor(),
                                                                _game->getPlayer()->getCurrentRoom())) {
                                            DM::say(_game->getPlayer()->getName() + " used a(n) " +
                                                    consumable->getName() +
                                                    ".");
                                            item->second -= 1;
                                            if (item->second == 0) {
                                                _inventory->erase(item->first);
                                            }
                                        } else {
                                            DM::say("This " + consumable->getName() +
                                                    " may be a bit too much to handle with the current unstable state of the dungeon....");
                                        }
                                    } else {
                                        DM::say("EY!! Don't go ruining my beautifull dungeon with a bomb without even a single monster to kill with it.");
                                    }
                                } else {
                                    consumable->use(_game->getPlayer());
                                    item->second -= 1;
                                    if (item->second == 0) {
                                        _inventory->erase(item->first);
                                    }
                                }
                            } else {
                                DM::say("You want to put WHAT WHERE?!?!");
                            }
                            break;
                        case InventoryState::DROP:
                            DM::say("Dropped a(n) " + item->first->getName());
                            item->second -= 1;
                            if (item->second == 0) {
                                _inventory->erase(item->first);
                            }
                            break;
                    }
                } else {
                    DM::say("You seem to have nothing left of this."); //TODO zou eigenlijk nooit moeten gebeuren
                }
            }
            if (done) {
                break;
            }
            ++i;
        }
        _state = InventoryState::STANDBY;
    } else {
        DM::say("You want to put WHAT WHERE?!?!");
    }
}

void MenuInventory::prepareForInput() {
    cout << ">";
//    switch (_state) {
//        case InventoryState::STANDBY:
//            break;
//        case InventoryState::EQUIP:
//            cout << "equip ";
//            break;
//        case InventoryState::USE:
//            cout << "use ";
//            break;
//        case InventoryState::DROP:
//            cout << "drop ";
//            break;
//    }
}
