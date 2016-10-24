//
// Created by Yorick on 19/10/2016.
//

#ifndef THE_ELDER_CODES_LINK_H
#define THE_ELDER_CODES_LINK_H

#include "Room.h"
#include "../enum/Direction.h"

class Room;

class Link {
    Room *_origin;
    Room *_target;
    int _keyLevel;
    bool _traveled;
    Direction _direction;
public:
    Link(Room *origin, Room *target, int keyLevel);

    ~Link() { };

    Room *travel(Room *origin, int keyLevel);

    int getKeyLevel() { return _keyLevel; };

    bool hasBeenUsedBefore() { return _traveled; };

    Direction getDirection(Room *origin = nullptr);
};


#endif //THE_ELDER_CODES_LINK_H
