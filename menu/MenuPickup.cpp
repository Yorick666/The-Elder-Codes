//
// Created by Yorick on 30/10/2016.
//

#include "MenuPickup.h"
#include "../Game.h"
#include "../enum/ConsumableType.h"
#include "../DM.h"
#include "../items/Consumable.h"
#include <regex>

using namespace std;

MenuPickup::MenuPickup(Game *game) : Menu(game) {

}

void MenuPickup::getViewScreen() {
    DM::say("\nItems on the ground:");
    map<Item *, int> *loot = _game->getCurrentRoom()->getLootList();
    int test = loot->size();
    int i = 1;
    for (map<Item *, int>::iterator item = loot->begin(); item != loot->end(); ++item) {
        switch (item->first->getItemType()) {
            case ItemType::ARMOR: {
                Armor *armor = (Armor *) item->first;
                DM::say("\t[" + to_string(i) + "]: " + item->first->getName() + " - " + to_string(armor->getBaseAC()) +
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

                DM::say("\t[" + to_string(i) + "]: " + item->first->getName() + " - " + type + " - " +
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
                        effect = "hp max per rest";
                        break;
                    case ConsumableType::HEALING:
                        type = "Healing item";
                        effect = "hp max on use";
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
                    DM::say("\t[" + to_string(i) + "]: " + consumable->getName() + " - " + type + " - " +
                            to_string(consumable->getBaseValue()) + " " + effect + " (" +
                            to_string(item->second) + "x)");
                } else {
                    DM::say("\t[" + to_string(i) + "]: " + consumable->getName() + " - " + type + " - " +
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
    DM::say("\nEnter the id of an item to pick it up or enter <back> to continue.");
}

void MenuPickup::loadOptions() {
    _options.push_back("[id]");
    _options.push_back("<b/back>");
}

void MenuPickup::handleInput(std::string input) {
    if (regex_match(input, regex("b|back"))) {
        _game->changeState(GameState::ROAMING);
    } else if (regex_match(input, regex("^\\d+$"))) {
        int x = stoi(input);
        int i = 1;
        map<Item *, int> *loot = _game->getCurrentRoom()->getLootList();
        for (map<Item *, int>::iterator item = loot->begin(); item != loot->end(); item++) {
            if (x == i) {
                if (item->second > 0) {
                    DM::say(_game->getPlayer()->getName() + " picks up a(n) " + item->first->getName());
                    _game->getPlayer()->addItemToInventory(item->first);
                    _game->getCurrentRoom()->removeItemFromLootList(item->first);
                    if (loot->size() <= 1) {
                        _game->changeState(GameState::ROAMING);
                    }
                    break;
                }
            }
        }
    }
}
