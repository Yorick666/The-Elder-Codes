//
// Created by Yorick on 18/10/2016.
//

#include "MenuFactory.h"
#include "MenuRoam.h"
#include "MenuFight.h"
#include "MenuInventory.h"
#include "MenuPickup.h"

Menu *MenuFactory::getMenu(Game *game, GameState state) {
    switch (state) {
        case GameState::STARTING :
            return new MenuStart(game);
        case GameState::ROAMING:
            return new MenuRoam(game);
        case GameState::FIGHTING:
            return new MenuFight(game);
        case GameState::INVENTORY:
            return new MenuInventory(game);
        case GameState::PICKUP:
            return new MenuPickup(game);
        case GameState::EXITING:
            break;
        case GameState::VICTORY:
            break;
    }
    return nullptr;
}
