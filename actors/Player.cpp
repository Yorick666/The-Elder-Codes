//
// Created by Yorick on 18/10/2016.
//
#include "Player.h"

using namespace std;

Player::Player(string name, int hp, int attack, int defense,
               int currentKeyLevel) : Actor(name,
                                            hp,
                                            attack,
                                            defense) {
    _keyLevel = currentKeyLevel;
}
