//
// Created by Yorick on 26/10/2016.
//

#include <c++/fstream>
#include <c++/sstream>
#include <algorithm>
#include "Loader.h"
#include "enum/ArmorType.h"
#include "items/Armor.h"
#include "items/Weapon.h"
#include "actors/Player.h"
#include "enum/ConsumableType.h"
#include "items/Consumable.h"
#include "DM.h"

using namespace std;

std::vector<Item *> Loader::loadItems() {
    vector<Item *> items;

    string line;

    int i = 1;

    try {
        ifstream weaponFile("weapons.txt");
        if (!weaponFile.is_open()) {
            weaponFile.open("D:\\GitHub\\The Elder Codes\\files\\weapons.txt");
        }
        while (!weaponFile.eof()) {
            getline(weaponFile, line);

            stringstream weaponStream(line);

            string name;
            int rarity;
            string type;
            int amountDice;
            int sizeDice;
            string subType;

            weaponStream >> name;
            weaponStream >> rarity;
            weaponStream >> type;
            weaponStream >> amountDice;
            weaponStream >> sizeDice;

            replace(name.begin(), name.end(), '_', ' ');
            WeaponType weaponType;
            if (type == "shield") {
                weaponType = WeaponType::SHIELD;
            } else if (type == "finesse") {
                weaponType = WeaponType::FINESSE;
            } else if (type == "heavy") {
                weaponType = WeaponType::HEAVY;
            } else if (type == "martial") {
                weaponType = WeaponType::MARTIAL;
            } else if (type == "simple") {
                weaponType = WeaponType::SIMPLE;
            } else {
                throw 1;
            }

            WeaponType subWeaponType = weaponType;
            if (weaponStream >> subType) {
                if (type == "shield") {
                    subWeaponType = WeaponType::SHIELD;
                } else if (type == "finesse") {
                    subWeaponType = WeaponType::FINESSE;
                } else if (type == "heavy") {
                    subWeaponType = WeaponType::HEAVY;
                } else if (type == "martial") {
                    subWeaponType = WeaponType::MARTIAL;
                } else if (type == "simple") {
                    subWeaponType = WeaponType::SIMPLE;
                } else {
                    throw 1;
                }
            }

            items.push_back(new Weapon(name, rarity, weaponType, amountDice, sizeDice, subWeaponType));
            i++;
        }
        weaponFile.close();
    } catch (int e) {
        DM::say("Something went wrong in line " + to_string(i) + " of your weapons file.", true);
    }

    i = 1;
    try {
        ifstream armorFile("armor.txt");
        if (!armorFile.is_open()) {
            armorFile.open("D:\\GitHub\\The Elder Codes\\files\\armor.txt");
        }

        while (!armorFile.eof()) {
            getline(armorFile, line);

            stringstream armorStream(line);

            string name;
            int rarity;
            string type;
            int baseAC;
            bool stealth;

            armorStream >> name;
            armorStream >> rarity;
            armorStream >> type;
            armorStream >> baseAC;
            armorStream >> stealth;

            replace(name.begin(), name.end(), '_', ' ');
            stealth = !stealth;
            ArmorType armorType;
            if (type == "heavy") {
                armorType = ArmorType::HEAVY;
            } else if (type == "medium") {
                armorType = ArmorType::MEDIUM;
            } else if (type == "light") {
                armorType = ArmorType::LIGHT;
            } else {
                throw 1;
            }
            items.push_back(new Armor(name, rarity, armorType, baseAC, stealth));
        }
        armorFile.close();
    } catch (int e) {
        DM::say("Something went wrong in line " + to_string(i) + " of your armor file.", true);
    }

    i = 1;

    try {
        ifstream consumableFile("consumables.txt");
        if (!consumableFile.is_open()) {
            consumableFile.open("D:\\GitHub\\The Elder Codes\\files\\consumables.txt");
        }

        while (!consumableFile.eof()) {
            getline(consumableFile, line);

            stringstream consumableStream(line);

            string name;
            int rarity;
            string type;
            int base;
            int amountDice;
            int sizeDice;

            consumableStream >> name;
            consumableStream >> rarity;
            consumableStream >> type;
            consumableStream >> base;
            consumableStream >> amountDice;
            consumableStream >> sizeDice;

            replace(name.begin(), name.end(), '_', ' ');
            ConsumableType consumableType;
            if (type == "healing") {
                consumableType = ConsumableType::HEALING;
            } else if (type == "illumination") {
                consumableType = ConsumableType::ILLUMINATION;
            } else if (type == "bomb") {
                consumableType = ConsumableType::BOMB;
            } else if (type == "talisman") {
                consumableType = ConsumableType::TALISMAN;
            } else if (type == "compass") {
                consumableType = ConsumableType::COMPASS;
            } else if (type == "food") {
                consumableType = ConsumableType::FOOD;
            } else {
                throw 1;
            }
            items.push_back(new Consumable(name, rarity, consumableType, base, amountDice, sizeDice));
        }
        consumableFile.close();
    } catch (int e) {
        DM::say("Something went wrong in line " + to_string(i) + " of your consumables file.", true);
    }

    return items;
}

std::map<Monster *, std::vector<Weapon *>> Loader::loadMonsters() {
    std::map<Monster *, std::vector<Weapon *>> monsters;

    string line = "";

    int i = 1;

    try {
        ifstream monsterFile("monsters.txt");
        if (!monsterFile.is_open()) {
            monsterFile.open("D:\\GitHub\\The Elder Codes\\files\\monsters.txt");
        }

        while (!monsterFile.eof()) {
            getline(monsterFile, line);

            stringstream monsterStream(line);

            string name;
            int exp;
            int hp;
            int str;
            int dex;
            int con;
            int prof;
            int armor;

            string weaponName;
            string weaponTypeString;
            int amount;
            int size;

            monsterStream >> name;
            monsterStream >> exp;
            monsterStream >> hp;
            monsterStream >> str;
            monsterStream >> dex;
            monsterStream >> con;
            monsterStream >> prof;
            monsterStream >> armor;

            replace(name.begin(), name.end(), '_', ' ');

            Monster *monster = new Monster(name, exp, hp, str, dex, con, prof, armor);

            monsterStream >> weaponName;
            monsterStream >> weaponTypeString;
            monsterStream >> amount;
            monsterStream >> size;

            replace(weaponName.begin(), weaponName.end(), '_', ' ');

            WeaponType weaponType;
            if (weaponTypeString == "shield") {
                weaponType = WeaponType::SHIELD;
            } else if (weaponTypeString == "finesse") {
                weaponType = WeaponType::FINESSE;
            } else if (weaponTypeString == "heavy") {
                weaponType = WeaponType::HEAVY;
            } else if (weaponTypeString == "martial") {
                weaponType = WeaponType::MARTIAL;
            } else if (weaponTypeString == "simple") {
                weaponType = WeaponType::SIMPLE;
            } else {
                throw 1;
            }

            monsters[monster].push_back(new Weapon(weaponName, 0, weaponType, amount, size, weaponType));

            if (monsterStream >> weaponName) {
                monsterStream >> weaponTypeString;
                monsterStream >> amount;
                monsterStream >> size;

                if (weaponTypeString == "shield") {
                    weaponType = WeaponType::SHIELD;
                } else if (weaponTypeString == "finesse") {
                    weaponType = WeaponType::FINESSE;
                } else if (weaponTypeString == "heavy") {
                    weaponType = WeaponType::HEAVY;
                } else if (weaponTypeString == "martial") {
                    weaponType = WeaponType::MARTIAL;
                } else if (weaponTypeString == "simple") {
                    weaponType = WeaponType::SIMPLE;
                } else {
                    throw 1;
                }
                monsters[monster].push_back(new Weapon(weaponName, 0, weaponType, amount, size, weaponType));
            }
        }
        monsterFile.close();
    } catch (int e) {
        DM::say("Something went wrong in line " + to_string(i) + " of your monsters file.", true);
    }

    return monsters;
}

Player *Loader::loadPlayer() {
    int i = 1;
    try {
        //TODO
    } catch (int e) {
        DM::say("Something went wrong in line " + to_string(i) + " of your player file.", true);
    }
    return nullptr;
}

void Loader::savePlayer(Player *player) {
    try {
        if (!player) {
            throw 1;
        }
        ofstream playerFile("player.txt");
        string name = player->getName();
        replace(name.begin(), name.end(), ' ', '_');
        playerFile << "Name " << name << endl;

        playerFile << "Level " << player->getLevel() << endl;

        playerFile << "Experience " << player->getExperience() << endl;

        playerFile << "Strength " << player->getStrength() << endl;

        playerFile << "Dexterity " << player->getDexterity() << endl;

        playerFile << "Constitution " << player->getConstitution() << endl;

        playerFile << "proficiency " << player->getProficiencyBonus() << endl;

        Weapon *weapon = player->getMainWeapon();
        name = weapon->getName();
        replace(name.begin(), name.end(), ' ', '_');
        string type = "";
        string subtype = "";
        switch (weapon->getWeaponType()) {
            case WeaponType::SIMPLE:
                type = "simple";
                break;
            case WeaponType::FINESSE:
                type = "finesse";
                break;
            case WeaponType::MARTIAL:
                type = "martial";
                break;
            case WeaponType::HEAVY:
                type = "heavy";
                break;
            case WeaponType::SHIELD:
                type = "shield";
                break;
        }
        switch (weapon->getWeaponSubType()) {
            case WeaponType::SIMPLE:
                subtype = "simple";
                break;
            case WeaponType::FINESSE:
                subtype = "finesse";
                break;
            case WeaponType::MARTIAL:
                subtype = "martial";
                break;
            case WeaponType::HEAVY:
                subtype = "heavy";
                break;
            case WeaponType::SHIELD:
                subtype = "shield";
                break;
        }
        playerFile << "Main_Weapon " << name << " " << weapon->getRarity() << " " << type << " " <<
        weapon->getDiceAmount() << " " << weapon->getDiceSize() << " " << subtype << endl;

        weapon = player->getOffHandWeapon();
        if (weapon) {
            name = weapon->getName();
            switch (weapon->getWeaponType()) {
                case WeaponType::SIMPLE:
                    type = "simple";
                    break;
                case WeaponType::FINESSE:
                    type = "finesse";
                    break;
                case WeaponType::MARTIAL:
                    type = "martial";
                    break;
                case WeaponType::HEAVY:
                    type = "heavy";
                    break;
                case WeaponType::SHIELD:
                    type = "shield";
                    break;
            }
            switch (weapon->getWeaponSubType()) {
                case WeaponType::SIMPLE:
                    subtype = "simple";
                    break;
                case WeaponType::FINESSE:
                    subtype = "finesse";
                    break;
                case WeaponType::MARTIAL:
                    subtype = "martial";
                    break;
                case WeaponType::HEAVY:
                    subtype = "heavy";
                    break;
                case WeaponType::SHIELD:
                    subtype = "shield";
                    break;
            }
            replace(name.begin(), name.end(), ' ', '_');
            playerFile << "Off_Weapon " << name << " " << weapon->getRarity() << " " << type << " " <<
            weapon->getDiceAmount() << " " << weapon->getDiceSize() << " " << subtype << endl;
        }

        Armor *armor = player->getArmor();
        name = armor->getName();
        replace(name.begin(), name.end(), ' ', '_');
        switch (armor->getArmorType()) {
            case ArmorType::LIGHT:
                type = "light";
                break;
            case ArmorType::MEDIUM:
                type = "medium";
                break;
            case ArmorType::HEAVY:
                type = "heavy";
                break;
        }
        playerFile << "Armor " << name << " " << armor->getRarity() << " " << type << " " << armor->getBaseAC() << endl;

        playerFile.close();
    } catch (int e) {
        DM::say("Something went wrong while saving your player data.", true);
    }
}
