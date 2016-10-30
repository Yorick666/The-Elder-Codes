//
// Created by Yorick on 18/10/2016.
//

#include <regex>
#include <c++/iostream>
#include "MenuStart.h"
#include "../DM.h"

using namespace std;

void MenuStart::handleInput(std::string input) {
    if (regex_match(input, regex("d|debug"))) {
        DM::say("Starting new game with debug mode on.", true);
        _game->startNewGame("Tester", true);
    } else if (regex_match(input, regex("s|standard"))) {
        string name;
        if (!_game->getPlayer()) {
            cout << "At least let me know the name of my next victim: ";
            cin >> name;
        }
        DM::say("Starting standard game.", true);
        _game->startNewGame(name);
    } else if (regex_match(input, regex("c|custom"))) {
        int size, roomsPerFloor, roomsPerLock;
        cout << "How many floors?";
        cin >> size;
        if (size <= 0) {
            size = 1;
        }

        cout << "How many rooms per floor? (min 10)";
        cin >> roomsPerFloor;
        if (roomsPerFloor < 10) {
            roomsPerFloor = 10;
        }

        cout << "How many locks per floor? (0-9)";
        cin >> roomsPerLock;
        if (roomsPerLock <= 0) {
            roomsPerLock = 0;
        } else if (roomsPerLock > 9) {
            roomsPerLock = roomsPerFloor / 9;
        } else {
            roomsPerLock = roomsPerFloor / roomsPerLock;
        }

        string name;
        if (!_game->getPlayer()) {
            cout << "At least let me know the name of my next victim: ";
            cin >> name;
        }

        DM::say("Starting custom game.", true);
        _game->startNewGame(name, true, size, roomsPerFloor, roomsPerLock);
    } else if (regex_match(input, regex("load"))) {
        _game->loadPlayer();
    } else if (regex_match(input, regex("new"))) {
        _game->resetPlayer();
    }
}

void MenuStart::loadOptions() {
    _options.push_back("<s/standard>");
    _options.push_back("<c/custom>");
    if (_game->getPlayer()) {
        _options.push_back("<new> character");
    } else {
        _options.push_back("<load> character");
    }
    _options.push_back("<exit>");
}

void MenuStart::getViewScreen() {
    DM::say("The Elder Codes - Algorithm of Time\n");

    _game->showHelpScreen();

    if (_game->getPlayer()) {
        DM::say("\nPlayer save file loaded!\n");
    }
}

MenuStart::MenuStart(Game *game) : Menu(game) {
}
