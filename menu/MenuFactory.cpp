//
// Created by Yorick on 18/10/2016.
//

#include "MenuFactory.h"
#include "MenuRoam.h"

Menu *MenuFactory::getMenu(Game * game, GameState state) {
    switch (state){
        case GameState::STARTING :
            return new MenuStart(game);
        case GameState::ROAMING:
            return new MenuRoam(game);
        case GameState::FIGHTING:break;
        case GameState::EXITING:break;
    }
    return nullptr;
}
