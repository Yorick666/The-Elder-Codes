//
// Created by Yorick on 27/10/2016.
//

#include <iostream>
#include <regex>
#include "MenuFight.h"
#include "../DM.h"

using namespace std;

MenuFight::MenuFight(Game *game) : Menu(game) {
}

void MenuFight::loadOptions() {
    _options.push_back("back");
}

void MenuFight::getViewScreen() {
    Room *currentRoom = _game->getCurrentRoom();
    if (currentRoom->hasMonsters()) {
        DM::say("\nYou see the following monsters:");
        const vector<Monster *> *monsters = currentRoom->getMonsters();
        for (int i = 0; i < monsters->size(); ++i) {
            DM::say("\t<" + to_string(i + 1) + ">: " + monsters->at(i)->getName() + " [" +
                    to_string(monsters->at(i)->getCurrentHp()) + "/" +
                    to_string(monsters->at(i)->getMaxHp()) + "]");
        }
    }
    DM::say("\nEnter the id of a monster to attack it or enter <back> to heal/run away.");
}

void MenuFight::handleInput(std::string input) {
    if (regex_match(input, regex("^\\d+$"))) {
        int x = stoi(input);
        vector<Monster *> *monsters = _game->getCurrentRoom()->getMonsters();
        int t = monsters->size();
        if (x <= monsters->size()) {
            _game->getPlayer()->attack(monsters->at(x - 1));
            if (!_game->getCurrentRoom()->hasLivingMonsters()) {
                DM::say("\n\nYou killed every monster in the room. Are you proud of yourself?");
                _game->changeState(GameState::ROAMING);
            } else {
                _game->monsterCombat();
            }
        } else {
            DM::say("ID-10T ERROR: Player is attacking an imaginary monster!");
        }
    } else if (regex_match(input, regex("b|back"))) {
        _game->changeState(GameState::ROAMING);
    } else {
        DM::say("Wut wut?");
    }
}

void MenuFight::prepareForInput() {
    cout << "[Life:" << _game->getPlayer()->getCurrentHp() << "/" << _game->getPlayer()->getMaxHp() << "]>";
}
