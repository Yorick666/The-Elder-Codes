//
// Created by Yorick on 18/10/2016.
//

#include "Room.h"

Room::Room(Coordinate coordinate, RoomType roomType, int keyLevel) {
    _coordinate = coordinate;
    _keyLevel = keyLevel;
    _type = roomType;
    _visited = false;

    if (coordinate.x == 0 && coordinate.y == 0) {
        throw 8;
    }
}

Room::~Room() {
    for (int i = 0; i < _links.size(); ++i) {
        delete _links[i];
    }
}
