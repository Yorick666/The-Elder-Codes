//
// Created by Yorick on 29/10/2016.
//

#include "Corridor.h"
#include "Room.h"

Corridor::Corridor(Room *first, Room *second, bool extraFlooral) {
    collapsed = false;
    _first = first;
    _second = second;

    if (extraFlooral){
        _first->addDoor(this,Direction::DOWN);
        _second->addDoor(this,Direction::UP);
    } else {
        _first->addDoor(this);
        _second->addDoor(this);
    }
}

Room *Corridor::otherSide(Room *room) const {
    return room == _first ? _second : _first;
}
