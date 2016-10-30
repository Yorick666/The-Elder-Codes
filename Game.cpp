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
    if (_input != "exit") {
        _menu->handleInput(_input);
    } else {
        _state = GameState::EXITING;
    }
    if (_player->getCurrentHp() == 0) {
        DM::say("GAME OVER!!!!!!!!!!! MUHAHAHAHA");
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

void Game::startNewGame(bool debug, int size, int roomsPerFloor, int roomsPerLock) {
    debugMode = debug;

    if (_dungeon) {
        delete _dungeon;
    }
    _dungeon = new Dungeon(debug, size, roomsPerFloor, roomsPerLock);

    if (!_player) {
        _player = new Player(_dungeon->getStartingRoom(), "Player");
        _player->generateStartingGear(&_items);
    }

//    _player = new Player(_dungeon->getStartingRoom(), "Player");
//    _player->generateStartingGear(&_items);

    generateMonsters(getCurrentRoom()); //TODO delete after finished debugging

    DM::say("Welcome hero, you're about to embark on a journey to defeat the master of this dungeon: The Dungeon Master. (Me!)");

    changeState(GameState::ROAMING);
}

void Game::generateMonsters(Room *room) {
    if (room->getMonsters()->size() > 0) {
        room->clearRoom();
        DM::say("New monstersForRoom enter the room....");
    }

    int playerLevel = _player->getLevel();
    int difficulty = Rng::roleDice(50);
    if (difficulty >= 45) {
        difficulty = 3;
    } else if (difficulty >= 30) {
        difficulty = 2;
    } else {
        difficulty = 1;
    }
    if (room->getRoomType() != RoomType::NORMAL) {
        difficulty = 4;
    }
    int baseExpMultiplier = 25;

    int expBudget = difficulty * playerLevel * baseExpMultiplier;

    vector<int> maxSizeMonsterOnLevel = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    vector<int> expToSize = {25, 50, 100, 200, 450, 700};
    vector<Monster *> monstersForRoom;

    int currentExp = 0;
    int currentSearchLevel = playerLevel;

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
                currentExp += tempMonster->getExperienceOnKill();
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
    if (!_player->getCurrentRoom()->hasLivingMonsters()) {
        if (Rng::roleDice(10) > 4) {
            Room *r = _player->getCurrentRoom()->getRoomBehindDoor(direction, _player->getSecurityLevel());
            if (r != nullptr) {
                generateMonsters(r);
            }
        }
        if (direction == Direction::UP) {
            _dungeon->ascend();
        }
        if (direction == Direction::DOWN) {
            _dungeon->descend();
        }
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
}

std::vector<Item *> Game::generateLoot(int monsterExp) {
    vector<Item *> loot;

    int rarity = Rng::roleDice(monsterExp * 2);

    while (true) {
        Item *item = _items[Rng::roleDice(_items.size()) - 1];
        if (item->getRarity() <= monsterExp * 2) {
            int amount = Rng::getRandomIntBetween(0, rarity / item->getRarity());
            rarity -= amount * item->getRarity();
            if (rarity > 0) {
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
    _player = Loader::loadPlayer();
}

void Game::savePlayer() {
    Loader::savePlayer(_player);
}
