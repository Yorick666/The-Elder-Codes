//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_MENU_H
#define THE_ELDER_CODES_MENU_H

#include <string>
#include <vector>

class Menu {

protected:
    std::vector<std::string> _options;

public:
    Menu() {};
    ~Menu() {};

    virtual void handleInput() { };
    std::string getMenuScreen();
};


#endif //THE_ELDER_CODES_MENU_H
