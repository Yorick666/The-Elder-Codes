//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include <iostream>
#include "MenuRoam.h"
#include "../DM.h"
#include "../items/Consumable.h"
#include "../Rng.h"

using namespace std;

void MenuRoam::loadOptions() {
    Room *currentRoom = _game->getCurrentRoom();

    _options.clear();
    if (currentRoom->hasMonsters()) {
        if (currentRoom->hasLivingMonsters()) {
            _options.push_back("<a/attack> [id]");
            _options.push_back("<f/flee>");
        } else {
            _options.push_back("<search>");
            _options.push_back("<r/rest>");
        }
    } else {
        if (currentRoom->getLootList()->size() > 0) {
            _options.push_back("<p/pickup> [id]");
        }
        _options.push_back("<r/rest>");
    }
    _options.push_back("<i/inventory>");
    _options.push_back("<stats>");
    _options.push_back("<m/map>");

    if (_game->isDebug()) {
        _options.push_back("<save>");
    }

    _options.push_back("<exit>");
}

void MenuRoam::getViewScreen() {
    Room *currentRoom = _game->getCurrentRoom();

    DM::showMap(_game->getCurrentFloor(), currentRoom, _game->isDebug(),
                _game->getPlayer()->getSecurityLevel(),
                true);

    DM::describeRoom(currentRoom);

    DM::say("\nYou see the following exits:");

    Corridor *targetCorridor = currentRoom->getCorridorBehindDoor(Direction::NORTH);
    Room *targetRoom = currentRoom->getRoomBehindDoor(Direction::NORTH);
    if (targetRoom) {
        if (targetCorridor && !targetCorridor->isCollapsed()) {
            Room *validRoom = currentRoom->getRoomBehindDoor(Direction::NORTH, _game->getPlayer()->getSecurityLevel());
            if (validRoom) {
                DM::say("\t An open door to the <n/north>.");
            } else {
                DM::say("\t A locked door to the north.");
            }
        } else {
            DM::say("\tA caved-in corridor to the north.");
        }
    }
    targetCorridor = currentRoom->getCorridorBehindDoor(Direction::EAST);
    targetRoom = currentRoom->getRoomBehindDoor(Direction::EAST);
    if (targetRoom) {
        if (targetCorridor && !targetCorridor->isCollapsed()) {
            Room *validRoom = currentRoom->getRoomBehindDoor(Direction::EAST, _game->getPlayer()->getSecurityLevel());
            if (validRoom) {
                DM::say("\t An open door to the <e/east>.");
            } else {
                DM::say("\t A locked door to the east.");
            }
        } else {
            DM::say("\tA caved-in corridor to the east.");
        }
    }
    targetCorridor = currentRoom->getCorridorBehindDoor(Direction::SOUTH);
    targetRoom = currentRoom->getRoomBehindDoor(Direction::SOUTH);
    if (targetRoom) {
        if (targetCorridor && !targetCorridor->isCollapsed()) {
            Room *validRoom = currentRoom->getRoomBehindDoor(Direction::SOUTH, _game->getPlayer()->getSecurityLevel());
            if (validRoom) {
                DM::say("\t An open door to the <s/south>.");
            } else {
                DM::say("\t A locked door to the south.");
            }
        } else {
            DM::say("\tA caved-in corridor to the south.");
        }
    }
    targetCorridor = currentRoom->getCorridorBehindDoor(Direction::WEST);
    targetRoom = currentRoom->getRoomBehindDoor(Direction::WEST);
    if (targetRoom) {
        if (targetCorridor && !targetCorridor->isCollapsed()) {
            Room *validRoom = currentRoom->getRoomBehindDoor(Direction::WEST, _game->getPlayer()->getSecurityLevel());
            if (validRoom) {
                DM::say("\t An open door to the <w/west>.");
            } else {
                DM::say("\t A locked door to the west.");
            }
        } else {
            DM::say("\tA caved-in corridor to the west.");
        }
    }
    if (currentRoom->getRoomType() == RoomType::EXIT) {
        if (currentRoom->hasLivingMonsters()) {
            DM::say("\t A Locked Golden Gate.");
        } else {
            DM::say("\t An unlocked Golden Gate. Could this be the <finish>?");
        }
    }
    if (currentRoom->getRoomType() == RoomType::DOWN) {
        if (!currentRoom->hasLivingMonsters()) {
            DM::say("\t An open hatch to the next floor <d/down> below.");
        } else {
            DM::say("\t A locked hatch on the floor.");
        }
    }
    if (currentRoom->getRoomType() == RoomType::UP) {
        if (!currentRoom->hasLivingMonsters()) {
            DM::say("\t An open hatch back to the previous floor <u/up>stairs.");
        } else {
            DM::say("\t A locked hatch on the ceiling.");
        }
    }

    if (currentRoom->hasMonsters()) {
        DM::say("\nYou see the following monsters:");
        const vector<Monster> *monsters = currentRoom->getMonsters();
        for (int i = 0; i < monsters->size(); ++i) {
            DM::say("\t[" + to_string(i + 1) + "]: " + monsters->at(i).getName() + " [" +
                    to_string(monsters->at(i).getCurrentHp()) + "/" +
                    to_string(monsters->at(i).getMaxHp()) + "]");
        }
    }

    if (currentRoom->getLootList()->size() > 0) {
        DM::say("\nItems on the ground:");
        map<Item *, int> *loot = _game->getCurrentRoom()->getLootList();
        int i = 1;
        for (map<Item *, int>::iterator item = loot->begin(); item != loot->end(); ++item) {
            switch (item->first->getItemType()) {
                case ItemType::ARMOR: {
                    Armor *armor = (Armor *) item->first;
                    string extra = "";
                    switch (armor->getArmorType()) {
                        case ArmorType::LIGHT:
                            extra = " + Dex ";
                            break;
                        case ArmorType::MEDIUM:
                            extra = " + max 2 Dex ";
                            break;
                        case ArmorType::HEAVY:
                            break;
                    }
                    DM::say("\t[" + to_string(i) + "]: " + item->first->getName() + " - AC: " +
                            to_string(armor->getBaseAC()) +
                            extra + "(" + to_string(item->second) + "x)");
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
                            type = "Shield (+2AC)";
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
    }
}

void MenuRoam::handleInput(std::string input) {
    Room *currentRoom = _game->getCurrentRoom();
    Player *player = _game->getPlayer();

    if (regex_match(input, regex("finish"))) {
        if (currentRoom->getRoomType() == RoomType::EXIT) {
            if (!currentRoom->hasLivingMonsters()) {
                _game->savePlayer();

                DM::say("Gratz!!!!!\nKeep playing!!!\n\n");

                _game->changeState(GameState::STARTING);
            } else {
                DM::say("Nice try, but first you have to get past my ultimate creation!!!!");
            }
        } else {
            DM::say("Wouldn't we all like to finish this game early?");
        }
    } else if (regex_match(input, regex("u|up"))) {
        if (player->travel(Direction::UP)) {
            _game->readyRoom(Direction::UP);
        }
    } else if (regex_match(input, regex("d|down"))) {
        if (player->travel(Direction::DOWN)) {
            _game->readyRoom(Direction::DOWN);
        }
    } else if (regex_match(input, regex("n|north"))) {
        if (player->travel(Direction::NORTH)) {
            _game->readyRoom(Direction::NORTH);
        }
    } else if (regex_match(input, regex("e|east"))) {
        if (player->travel(Direction::EAST)) {
            _game->readyRoom(Direction::EAST);
        }
    } else if (regex_match(input, regex("s|south"))) {
        if (player->travel(Direction::SOUTH)) {
            _game->readyRoom(Direction::SOUTH);
        }
    } else if (regex_match(input, regex("w|west"))) {
        if (player->travel(Direction::WEST)) {
            _game->readyRoom(Direction::WEST);
        }
    } else if (regex_match(input, regex("m|map"))) {
        DM::showMap(_game->getCurrentFloor(), currentRoom, _game->isDebug(),
                    player->getSecurityLevel());
    } else if (regex_match(input, regex("a|attack|fight|kill"))) {
        if (currentRoom->hasLivingMonsters()) {
            _game->changeState(GameState::FIGHTING);
        } else {
            DM::say("uhm, fight what exactly?");
        }
    } else if (regex_match(input, regex("f|flee"))) {
        _game->flee();
    } else if (regex_match(input, regex("i|inventory"))) {
        _game->changeState(GameState::INVENTORY);
    } else if (regex_match(input, regex("r|rest"))) {
        if (!currentRoom->hasLivingMonsters()) {
            map<Item *, int> *inventory = player->getInventory();
            bool rested = false;
            for (map<Item *, int>::iterator item = inventory->begin(); item != inventory->end(); item++) {
                if (item->first->getItemType() == ItemType::CONSUMABLE) {
                    Consumable *consumable = (Consumable *) item->first;
                    if (consumable->getConsumableType() == ConsumableType::FOOD) {
                        consumable->use(player);
                        item->second -= 1;
                        if (item->second == 0) {
                            inventory->erase(item->first);
                        }
                        rested = true;
                        player->checkForLevelUp();
                        _game->savePlayer();
                        if (Rng::roleDice(10) > 7) {
                            _game->generateMonsters(currentRoom);
                        }
                        break;
                    }
                }
            }
            if (!rested) {
                DM::say("You don't have any food, so resting won't help you a lot.");
            }
        } else {
            DM::say("Why try to rest here? Being brave is almost the same as being stupid.");
        }
    } else if (regex_match(input, regex("search"))) {
        if (!currentRoom->hasLivingMonsters()) {
            _game->checkDeadMonsters();
        } else {
            DM::say("Do you really want to loot so bad?");
        }
    } else if (regex_match(input, regex("stats"))) {
        DM::say("--------STATS--------");
        DM::say("Name:\t\t" + player->getName());
        DM::say("Security Level:\t" + to_string(player->getSecurityLevel()));
        DM::say("HP:\t\t" + to_string(player->getCurrentHp()) + "/" + to_string(player->getMaxHp()));
        DM::say("Exp:\t\t" + to_string(player->getExperience()) + "/" +
                to_string((int) pow(3, player->getLevel()) * 100));
        DM::say("Strength:\t" + to_string(player->getStrength()));
        DM::say("Dexterity:\t" + to_string(player->getDexterity()));
        DM::say("Constitution:\t" + to_string(player->getConstitution()));
        DM::say("Proficiency:\t" + to_string(player->getProficiencyBonus()));

        int AC = 0;
        if (player->getArmor()) {
            AC += player->getArmor()->getBaseAC();
            AC += player->getArmor()->getMaxDex(player->getDexterity());
        } else {
            AC += player->getNaturalArmor() + player->getDexterity();
        }
        if (player->getOffHandWeapon() && player->getOffHandWeapon()->getWeaponType() == WeaponType::SHIELD) {
            AC += 2;
        }

        DM::say("Total AC:\t" + to_string(AC));

        Weapon *main = player->getMainWeapon();
        if (main) {
            int base = player->getStrength();
            string type = "";
            switch (main->getWeaponType()) {
                case WeaponType::SIMPLE:
                    type = "Simple Weapon (Str)";
                    break;
                case WeaponType::FINESSE:
                    if (player->getDexterity() > player->getStrength()) {
                        base = player->getDexterity();
                    }
                    type = "Finesse Weapon (Str or Dex)";
                    break;
                case WeaponType::MARTIAL:
                    type = "Martial Weapon (Str)";
                    break;
                case WeaponType::HEAVY:
                    type = "heavy Weapon (Str)";
                    break;
                case WeaponType::SHIELD:
                    type = "Shield (Str)";
                    break;
            }

            DM::say("Main Weapon:\t" + main->getName() + " (" + to_string(main->getDiceAmount()) + "d" +
                    to_string(main->getDiceSize()) + "+" + to_string(base) + " " + type + ")");
        } else {
            DM::say("Main Weapon:\tNone");
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
                    type = "Shield (+2 AC)";
                    break;
            }

            DM::say("Offhand Weapon:\t" + off->getName() + " (" + to_string(off->getDiceAmount()) + "d" +
                    to_string(off->getDiceSize()) + "+" + to_string(base) + " " + type + ")");
        } else {
            DM::say("Offhand Weapon:\tNone");
        }


        Armor *armor = player->getArmor();
        if (armor) {
            string extra = "";
            switch (armor->getArmorType()) {
                case ArmorType::LIGHT:
                    extra = " + Dex ";
                    break;
                case ArmorType::MEDIUM:
                    extra = " + max 2 Dex ";
                    break;
                case ArmorType::HEAVY:
                    break;
            }

            DM::say("Armor:\t" + armor->getName() + " ( AC: " + to_string(armor->getBaseAC()) + extra + ")");
        } else {
            DM::say("Armor:\tNone");
        }
    } else if (regex_match(input, regex("p|pickup"))) {
        if (currentRoom->getLootList()->size() > 0) {
            _game->changeState(GameState::PICKUP);
        } else {
            DM::say("Wanting to have stuff doesn't make it appear out of thin air.");
        }
    } else if (_game->isDebug() && regex_match(input, regex("save"))) {
        _game->savePlayer();
    } else {
        DM::say("Come again for big fudge?");
    }
}

MenuRoam::MenuRoam(Game *game) : Menu(game) {
//    loadOptions();
}

void MenuRoam::prepareForInput() {
    DM::say("[Life:" +
            to_string(_game->getPlayer()->getCurrentHp()) + "/" + to_string(_game->getPlayer()->getMaxHp()) + "]>",
            true,
            false);
}
