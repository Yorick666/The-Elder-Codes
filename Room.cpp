//
// Created by Yorick on 18/10/2016.
//

#include "Room.h"

Room::Room(Coordinate *coordinate, Room *parent, RoomType roomType, int keyLevel) {
    _coordinate = coordinate;
    _keyLevel = keyLevel;
    _type = roomType;
}

Room::~Room() {
    delete _coordinate;
}
