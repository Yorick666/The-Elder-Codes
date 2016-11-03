//
// Created by Yorick on 26/10/2016.
//

#include <fstream>
#include <sstream>
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
            i++;
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
            i++;
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
                i++;
            }
        }
        monsterFile.close();
    } catch (int e) {
        DM::say("Something went wrong in line " + to_string(i) + " of your monsters file.", true);
    }

    return monsters;
}

Player *Loader::loadPlayer(vector<Item *> items) {
    Player *player = nullptr;
    try {
        ifstream playerFile("player.txt");
        if (!playerFile.is_open()) {
            playerFile.open("D:\\GitHub\\The Elder Codes\\files\\player.txt");
        }

        if (!playerFile.is_open()) {
            throw -1;
        }

        string line;

        string stat;
        stringstream playerStream;


        string name;
        getline(playerFile, line);
        playerStream.str(line);
        playerStream >> stat;
        if (stat == "Name") {
            playerStream >> name;
        } else {
            throw 1;
        }

        int level;
        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        if (stat == "Level") {
            playerStream >> level;
        } else {
            throw 2;
        }


        int exp;
        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        if (stat == "Experience") {
            playerStream >> exp;
        } else {
            throw 3;
        }


        int hp;
        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        if (stat == "Hp") {
            playerStream >> hp;
        } else {
            throw 4;
        }


        int str;
        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        if (stat == "Strength") {
            playerStream >> str;
        } else {
            throw 5;
        }


        int dex;
        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        if (stat == "Dexterity") {
            playerStream >> dex;
        } else {
            throw 6;
        }


        int con;
        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        if (stat == "Constitution") {
            playerStream >> con;
        } else {
            throw 7;
        }


        int prof;
        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        if (stat == "Proficiency") {
            playerStream >> prof;
        } else {
            throw 8;
        }

        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        Weapon *main;
        if (stat == "Main_Weapon") {
            string name;
            playerStream >> name;

            replace(name.begin(), name.end(), '_', ' ');

            bool existing = false;
            for (Item *item: items) {
                if (item->getName() == name && item->getItemType() == ItemType::WEAPON) {
                    existing = true;
                    main = (Weapon *) item;
                }
            }
            if (!existing) {
                int rarity;
                string type;
                int amountDice;
                int sizeDice;
                string subType;

                playerStream >> rarity;
                playerStream >> type;
                playerStream >> amountDice;
                playerStream >> sizeDice;

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
                    throw 9;
                }

                WeaponType subWeaponType = weaponType;
                if (playerStream >> subType) {
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
                        throw 9;
                    }
                }

                main = new Weapon(name, rarity, weaponType, amountDice, sizeDice, subWeaponType);
                items.push_back(main);
            }
        } else {
            throw 9;
        }

        getline(playerFile, line);
        playerStream.clear();
        playerStream.str(line);
        playerStream >> stat;
        Weapon *off = nullptr;
        if (stat == "Off_Weapon") {
            string name;
            playerStream >> name;

            replace(name.begin(), name.end(), '_', ' ');

            bool existing = false;
            for (Item *item: items) {
                if (item->getName() == name && item->getItemType() == ItemType::WEAPON) {
                    existing = true;
                    off = (Weapon *) item;
                }
            }
            if (!existing) {
                int rarity;
                string type;
                int amountDice;
                int sizeDice;
                string subType;

                playerStream >> rarity;
                playerStream >> type;
                playerStream >> amountDice;
                playerStream >> sizeDice;

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
                    throw 10;
                }

                WeaponType subWeaponType = weaponType;
                if (playerStream >> subType) {
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
                        throw 10;
                    }
                }

                off = new Weapon(name, rarity, weaponType, amountDice, sizeDice, subWeaponType);
                items.push_back(off);
            }
            getline(playerFile, line);
            playerStream.clear();
            playerStream.str(line);
            playerStream >> stat;
        }


        Armor *armor = nullptr;
        if (stat == "Armor") {
            string name;
            playerStream >> name;

            replace(name.begin(), name.end(), '_', ' ');

            bool existing = false;
            for (Item *item: items) {
                if (item->getName() == name && item->getItemType() == ItemType::ARMOR) {
                    existing = true;
                    armor = (Armor *) item;
                }
            }
            if (!existing) {

                int rarity;
                string type;
                int baseAC;

                playerStream >> rarity;
                playerStream >> type;
                playerStream >> baseAC;

                ArmorType armorType;
                if (type == "heavy") {
                    armorType = ArmorType::HEAVY;
                } else if (type == "medium") {
                    armorType = ArmorType::MEDIUM;
                } else if (type == "light") {
                    armorType = ArmorType::LIGHT;
                } else {
                    throw 11;
                }
                armor = new Armor(name, rarity, armorType, baseAC, false); //TODO IN FUTURE STEALTH
                items.push_back(armor);
            }
        } else {
            throw 11;
        }

        player = new Player(nullptr, name, hp, str, dex, con, prof, level, exp);
        player->equip(main);
        player->equip(off);
        player->equip(armor);

    } catch (int e) {
        delete player;
        if (e < 0) {
            DM::say("Ok, where did you put that poor file?\n");
        } else {
            DM::say("Something went wrong while loading line " + to_string(e) + " in your player file.");
        }
    }
    return player;
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

        playerFile << "Hp " << player->getMaxHp() << endl;

        playerFile << "Strength " << player->getStrength() << endl;

        playerFile << "Dexterity " << player->getDexterity() << endl;

        playerFile << "Constitution " << player->getConstitution() << endl;

        playerFile << "Proficiency " << player->getProficiencyBonus() << endl;

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
        DM::say("Save succesful!");
    } catch (int e) {
        DM::say("Something went wrong while saving your player data.", true);
    }
}
