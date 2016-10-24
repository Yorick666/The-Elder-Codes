//
// Created by Yorick on 18/10/2016.
//

#include <iostream>
#include "Menu.h"
#include "../DM.h"

using namespace std;

void Menu::getMenuScreen() {
    getViewScreen();

    cout << endl;

    DM::getInstance()->showOutput();

    cout << endl;

    string top = "";
    string mid = "";
    string bot = "";
    for (int i = 0; i < _options.size(); i++) {
        if (i == 0) {
            top += char(201);
            mid += char(186);
            bot += char(200);
        }
        for (int j = 0; j <= _options[i].size() + 1; ++j) {
            top += char(205);
            bot += char(205);
        }
        if (i == _options.size() - 1) {
            top += char(187);
            bot += char(188);
        } else {
            top += char(203);
            bot += char(202);
        }
        mid += " " + _options[i] + " ";
        mid += char(186);
    }
    string result = top + "\n" + mid + "\n" + bot;
    cout << result << endl;
}

void Menu::prepareForInput() {
    cout << ">";
}

Menu::Menu(Game *game) {
    _game = game;
}
