//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_MENUROAM_H
#define THE_ELDER_CODES_MENUROAM_H

#include "Menu.h"

class Game;

class MenuRoam : public Menu {
    void getViewScreen();
    void loadOptions();

public:
    MenuRoam(Game *game);

    ~MenuRoam() { };

    bool handleInput(std::string input);

    void prepareForInput();
};


#endif //THE_ELDER_CODES_MENUROAM_H
