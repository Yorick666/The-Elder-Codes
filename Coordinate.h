//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_COORDINATE_H
#define THE_ELDER_CODES_COORDINATE_H


class Coordinate {
public:
    Coordinate() {
        this->x = 0;
        this->y = 0;
    };

    Coordinate(int x, int y) {
        this->x = x;
        this->y = y;
    };

    int x, y;

    bool operator==(Coordinate b) { return this->x == b.x && this->y == b.y; };

    bool operator!=(Coordinate b) { return this->x != b.x || this->y != b.y; };

};


#endif //THE_ELDER_CODES_COORDINATE_H
