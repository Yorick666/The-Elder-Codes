//
// Created by Yorick on 19/10/2016.
//

#include "Link.h"

Link::Link(Room *room1, Room *room2, int keyLevel) {
    _room1 = room1;
    _room2 = room2;
    _keyLevel = keyLevel;
}

Room *Link::travel(Room *origin, int keyLevel) {
    if (keyLevel >= _keyLevel) {
        if (_room1 == origin) {
            return _room2;
        }

        if (_room2 == origin) {
            return _room1;
        }
    }

    return nullptr;
}

int Link::getKeyLevel() {
    return _keyLevel;
}
