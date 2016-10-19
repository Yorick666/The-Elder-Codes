//
// Created by Yorick on 19/10/2016.
//

#ifndef THE_ELDER_CODES_LINK_H
#define THE_ELDER_CODES_LINK_H

#include "Room.h"
class Room;
class Link {
    Room * _room1;
    Room * _room2;
    int _keyLevel;
public:
    Link(Room *room1, Room *room2, int keyLevel = 0);

    Room *travel(Room *origin, int keyLevel);

    int getKeyLevel();
};


#endif //THE_ELDER_CODES_LINK_H
