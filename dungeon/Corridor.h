//
// Created by Yorick on 29/10/2016.
//

#ifndef THE_ELDER_CODES_CORRIDOR_H
#define THE_ELDER_CODES_CORRIDOR_H


class Room;

class Corridor {
    Room *_first;
    Room *_second;
    bool collapsed;

public:
    Corridor(Room *first, Room *second);

    void collapse() { collapsed = true; }

    bool isCollapsed() const { return collapsed; }

    Room *otherSide(Room *room) const;

    Room *getFirstRoom() const { return _first; }

    Room *getSecondRoom() const { return _second; }
};


#endif //THE_ELDER_CODES_CORRIDOR_H
