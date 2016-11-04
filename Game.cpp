//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include <conio.h>
#include "Game.h"
#include "menu/MenuFactory.h"
#include "DM.h"
#include "Loader.h"
#include "Rng.h"

using namespace std;

Game::Game() {
    _items = Loader::loadItems();
    _monsters = Loader::loadMonsters();

    if (_items.size() == 0 || _monsters.size() == 0) {
        throw 1;
    }

    _menu = nullptr;
    _dungeon = nullptr;
    _player = nullptr;
}

Game::~Game() {
    delete _menu;
    delete _dungeon;
    delete _player;
    for (Item *item : _items) {
        if (item) {
            delete item;
        }
    }

    for (auto iter:_monsters) {
        if (iter.first) {
            delete iter.first;
        }
        for (Weapon *weapon:iter.second) {
            if (weapon) {
                delete weapon;
            }
        }
    }
}

void Game::showScreen() {
    _menu->getMenuScreen();
}

GameState Game::getGameState() {
    return _state;
}

void Game::getInput() {
    _menu->prepareForInput();
    _input = DM::askInput();

    if (_input == "help") {
        showHelpScreen();
    } else if (_input != "exit") {
        _menu->handleInput(_input);
    } else {
        _state = GameState::EXITING;
    }
    if (_player && _player->getCurrentHp() == 0) {
        DM::say("\n\n\nGAME OVER!!!!!!!!!!! MUHAHAHAHA");
        DM::getInstance()->showOutput();
        getch();
        _state = GameState::EXITING;
    }
}

void Game::changeState(GameState newState) {
    _state = newState;
    Menu *temp = MenuFactory::getMenu(this, newState);
    if (temp) {
        if (_menu) {
            delete _menu;
        }
        _menu = temp;
    }
}

void Game::startNewGame(string playerName, bool debug, int size, int roomsPerFloor, int roomsPerLock) {
    debugMode = debug;

    if (_dungeon) {
        delete _dungeon;
    }
    _dungeon = new Dungeon(debug, size, roomsPerFloor, roomsPerLock);

    if (!_player) {
        _player = new Player(_dungeon->getStartingRoom(), playerName);
    } else {
        Player *temp = new Player(_dungeon->getStartingRoom(), _player);
        delete _player;
        _player = temp;
    }
    generateStartingGear();

    DM::say("Welcome " + _player->getName() +
            ", you're about to embark on a journey to defeat the master of this dungeon: The Dungeon Master. (Me!)\n");

    changeState(GameState::ROAMING);
}

void Game::generateMonsters(Room *room) {
    if (room->getMonsters()->size() > 0) {
        room->clearRoom();
    }

    int level = _dungeon->getCurrentLevel() + 1;
//    int level = _player->getLevel();
    int difficulty = Rng::roleDice(50);

    if (difficulty >= 45) {
        difficulty = 3;
    } else if (difficulty >= 30) {
        difficulty = 2;
    } else {
        difficulty = 1;
    }

    if (room->getRoomType() == RoomType::EXIT) {
        difficulty = 4;
    }
    if (room->getRoomType() == RoomType::DOWN) {
        difficulty = 3;
    }

    int baseExpMultiplier = 25;

    int expBudget = difficulty * level * baseExpMultiplier;

    vector<int> maxSizeMonsterOnLevel = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    vector<int> expToSize = {25, 50, 100, 200, 450, 700};
    vector<Monster *> monstersForRoom;

    int currentExp = 0;
    int currentSearchLevel = level;

    vector<Monster *> monsterList;

    for (auto iter:_monsters) {
        monsterList.push_back(iter.first);
    }

    while (true) {
        bool foundOne = false;
        for (int i = 0; i < 20; ++i) {
            Monster *tempMonster = monsterList.at(Rng::roleDice(monsterList.size()) - 1);
            if (expBudget - currentExp >= tempMonster->getExperienceOnKill() &&
                tempMonster->getExperienceOnKill() <= expToSize[maxSizeMonsterOnLevel[currentSearchLevel]]) {
                currentExp += tempMonster->getExperienceOnKill() * pow(1.5, monstersForRoom.size());
                monstersForRoom.push_back(tempMonster);
                foundOne = true;
                break;
            }
        }
        if (!foundOne) {
            currentSearchLevel--;
        }
        if (currentSearchLevel == 0) {
            break;
        }
    }

    for (Monster *monster : monstersForRoom) {
        Monster m = *monster;
        if (_monsters[monster].size() > 0) {
            m.addMainAttack(_monsters[monster][0]);
        }
        if (_monsters[monster].size() > 1) {
            m.addSecondAttack(_monsters[monster][1]);
        }
        getCurrentRoom()->addMonster(m);
    }
}

void Game::flee() {
    if (getCurrentRoom()->hasLivingMonsters()) {
        int chance = Rng::roleDice(10);
        if (chance > 5) {
            _player->flee();
            readyRoom();
        } else {
            DM::say("You failed to flee, giving the monsters a chance to attack you.");
            monsterCombat();
        }
    } else {
        DM::say("Flee from what exactly?");
    }
}

void Game::monsterCombat() {
    vector<Monster> *monsters = getCurrentRoom()->getMonsters();
    for (int m = 0; m < monsters->size(); ++m) {
        monsters->at(m).attack(_player);
    }
}

void Game::readyRoom(Direction direction) {
    Room *r = _player->getCurrentRoom();
    if (r) {
        if (r->getRoomType() == RoomType::UPGRADE &&
            r->getSecurityLevel() == _player->getSecurityLevel()) {
            _player->upgradeSecurityLevel();
        }

        if (Rng::roleDice(10) > 6 || r->getRoomType() == RoomType::DOWN || r->getRoomType() == RoomType::EXIT) {
            generateMonsters(r);
        }
        if (direction == Direction::UP) {
            _dungeon->ascend();
        }
        if (direction == Direction::DOWN) {
            _dungeon->descend();
        }

        if (!r->visited() && Rng::roleDice(10) > 6) {
            int rarity = Rng::roleDice(100);
            int chances = 100;
            while (chances > 0) {
                Item *item = _items[Rng::roleDice(_items.size()) - 1];
                if (item->getRarity() <= rarity) {
                    r->addItemToLootList(item);
                    break;
                }
                chances--;
            }
        }

        r->visit();
    }
}

void Game::checkDeadMonsters() {
    vector<Monster> *monsters = getCurrentRoom()->getMonsters();

    for (int m = 0; m < monsters->size(); ++m) {
        if (monsters->at(m).getCurrentHp() <= 0) {
            DM::say(monsters->at(m).getName() + " searched and " + _player->getName() + " gains " +
                    to_string(monsters->at(m).getExperienceOnKill()) + " xp!");
            _player->gainExperience(monsters->at(m).getExperienceOnKill());

            vector<Item *> loot = generateLoot(monsters->at(m).getExperienceOnKill());

            for (Item *item : loot) {
                DM::say(_player->getName() + " picks up a(n) " + item->getName());
                _player->addItemToInventory(item);
            }
            monsters->erase(monsters->begin() + m);
        }
    }

    if (_player->getExperience() >= pow(3, _player->getLevel()) * 100) {
        DM::say("\nYou should get some <rest> so you can level up.\n");
    }
}

std::vector<Item *> Game::generateLoot(int monsterExp) {
    vector<Item *> loot;

    int rarity = Rng::roleDice(monsterExp * 2);
    int max = rarity;
    while (true) {
        Item *item = _items[Rng::roleDice(_items.size()) - 1];
        if (item->getRarity() <= max && item->getRarity() > 0) {
            int amount = Rng::getRandomIntBetween(0, rarity / item->getRarity());
            if (amount > 3) {
                amount = 3;
            }
            rarity -= amount * item->getRarity();
            if (item->getItemType() != ItemType::CONSUMABLE) {
                amount = 1;
            }
            if (rarity > 0 && rarity >= item->getRarity() && Rng::roleDice(4) > 1) {
                for (int i = 0; i < amount; ++i) {
                    loot.push_back(item);
                }
            } else {
                break;
            }
        }
    }
    return loot;
}

void Game::loadPlayer() {
    _player = Loader::loadPlayer(_items);
}

void Game::savePlayer() {
    Loader::savePlayer(_player);
}

void Game::resetPlayer() {
    delete _player;
    _player = nullptr;
}

void Game::showHelpScreen() const {
    DM::say("Remember:\n\t- Enter <exit> at anytime to exit the game.\n\t- <t/this> tells you that you can enter 'this' or 't' in the console (without the '').\n\t- <this> [id] means you can enter 'this 1' in the console (if there is something with 1 as id).\n\t- Feel free to ask for <help> at any time.");
}

void Game::generateStartingGear() {
    vector<Weapon *> weaponPicker;
    vector<Armor *> armorPicker;
    for (int i = 0; i <= _items.size(); ++i) {
        if (i < _items.size()) {
            Item *item = _items.at(i);
            if (item) {
                if (item->getItemType() == ItemType::WEAPON) {
                    if (item->getRarity() <= 10) {
                        weaponPicker.push_back((Weapon *) item);
                    }
                } else if (item->getItemType() == ItemType::ARMOR) {
                    if (item->getRarity() <= 10) {
                        armorPicker.push_back((Armor *) item);
                    }
                } else if (item->getItemType() == ItemType::CONSUMABLE) {
                    if (item->getRarity() <= 10) {
                        _player->addItemToInventory(item);
                        _player->addItemToInventory(item);
                    }
                }
            }
        } else {
            if (!_player->getMainWeapon()) {
                _player->equip(weaponPicker[Rng::getRandomIntBetween(0, weaponPicker.size() - 1)]);
            }
            if (!_player->getArmor()) {
                _player->equip(armorPicker[Rng::getRandomIntBetween(0, armorPicker.size() - 1)]);
            }

            //TODO test
            _player->addItemToInventory(weaponPicker[Rng::getRandomIntBetween(0, weaponPicker.size() - 1)]);
            _player->addItemToInventory(weaponPicker[Rng::getRandomIntBetween(0, weaponPicker.size() - 1)]);
            _player->addItemToInventory(armorPicker[Rng::getRandomIntBetween(0, armorPicker.size() - 1)]);
        }
    }
}
