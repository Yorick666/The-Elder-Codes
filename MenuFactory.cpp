//
// Created by Yorick on 18/10/2016.
//

#include "MenuFactory.h"

MenuFactory *MenuFactory::_instance = nullptr;

MenuFactory *MenuFactory::getInstance() {
    if (!_instance) {
        _instance = new MenuFactory();
    }
    return _instance;
}

Menu *MenuFactory::getMenu(GameState state) {
    switch (state){
        case GameState::STARTING :
            return new MenuStart();
        case GameState::ROAMING:break;
        case GameState::FIGHTING:break;
        case GameState::EXITING:break;
    }
    return nullptr;
}
