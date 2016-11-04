//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_MENUROAM_H
#define THE_ELDER_CODES_MENUROAM_H

#include "Menu.h"

class Game;

class MenuRoam : public Menu {
    void loadOptions();

    void getViewScreen();

public:
    MenuRoam(Game *game);

    ~MenuRoam() { };

    void handleInput(std::string input);

    void prepareForInput();
};


#endif //THE_ELDER_CODES_MENUROAM_H
