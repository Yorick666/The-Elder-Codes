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
            DM::say("At least let me know the name of my next victim.\n>", true, false);
            name = DM::askInput();
        }
        DM::say("Starting standard game.", true);
        _game->startNewGame(name);
    } else if (regex_match(input, regex("c|custom"))) {
        int size, roomsPerFloor, locksPerFloor, roomsPerLock;
        string input;
        DM::say("How many floors?\n>", true, false);
        input = DM::askInput();
        size = stoi(input);
        if (size <= 0) {
            size = 1;
        }

        DM::say("How many rooms per floor? (min 10)\n>", true, false);
        input = DM::askInput();
        roomsPerFloor = stoi(input);
        if (roomsPerFloor < 10) {
            roomsPerFloor = 10;
        }

        DM::say("How many locks per floor? (0-9)\n>", true, false);
        input = DM::askInput();
        locksPerFloor = stoi(input);
        if (locksPerFloor <= 0) {
            roomsPerLock = 0;
        } else if (locksPerFloor > 9) {
            roomsPerLock = roomsPerFloor / 9;
        } else {
            roomsPerLock = roomsPerFloor / locksPerFloor;
        }

        string name;
        if (!_game->getPlayer()) {
            DM::say("At least let me know the name of my next victim.\n>", true, false);
            name = DM::askInput();
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
    _options.push_back("<s/standard> dungeon");
    _options.push_back("<c/custom> dungeon");
    if (_game->getPlayer()) {
        _options.push_back("<new> character");
    } else {
        _options.push_back("<load> character");
    }
    _options.push_back("<exit>");
}

void MenuStart::getViewScreen() {
    DM::say("       _______ _            ______ _     _              _____          _           \n"
                    "      |__   __| |          |  ____| |   | |            / ____|        | |          \n"
                    "         | |  | |__   ___  | |__  | | __| | ___ _ __  | |     ___   __| | ___  ___ \n"
                    "         | |  | '_ \\ / _ \\ |  __| | |/ _` |/ _ \\ '__| | |    / _ \\ / _` |/ _ \\/ __|\n"
                    "         | |  | | | |  __/ | |____| | (_| |  __/ |    | |___| (_) | (_| |  __/\\__ \\\n"
                    "         |_|  |_| |_|\\___| |______|_|\\__,_|\\___|_|     \\_____\\___/ \\__,_|\\___||___/");

    DM::say("     _    _                  _ _   _                        __   _____ _                \n"
                    "    / \\  | | __ _  ___  _ __(_) |_| |__  _ __ ___     ___  / _| |_   _(_)_ __ ___   ___ \n"
                    "   / _ \\ | |/ _` |/ _ \\| '__| | __| '_ \\| '_ ` _ \\   / _ \\| |_    | | | | '_ ` _ \\ / _ \\\n"
                    "  / ___ \\| | (_| | (_) | |  | | |_| | | | | | | | | | (_) |  _|   | | | | | | | | |  __/\n"
                    " /_/   \\_\\_|\\__, |\\___/|_|  |_|\\__|_| |_|_| |_| |_|  \\___/|_|     |_| |_|_| |_| |_|\\___|\n"
                    "            |___/                                                                       \n");

    _game->showHelpScreen();

    if (_game->getPlayer()) {
        DM::say("\nPlayer save file loaded!");
    }
}

MenuStart::MenuStart(Game *game) : Menu(game) {
}
