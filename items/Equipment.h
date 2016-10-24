//
// Created by Yorick on 20/10/2016.
//

#ifndef THE_ELDER_CODES_EQUIPMENT_H
#define THE_ELDER_CODES_EQUIPMENT_H


#include "Item.h"

class Equipment : public Item {
protected:
    bool equiped;
public:
    Equipment();

    bool use() { return false; };

    bool usable() { return false; };

    bool equip() { return false; };
};


#endif //THE_ELDER_CODES_EQUIPMENT_H
