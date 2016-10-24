//
// Created by Yorick on 21/10/2016.
//

#ifndef THE_ELDER_CODES_ITEM_H
#define THE_ELDER_CODES_ITEM_H


class Item {
public:
    virtual bool use() = 0;

    virtual bool usable() = 0;

    virtual bool drop() = 0;
};


#endif //THE_ELDER_CODES_ITEM_H
