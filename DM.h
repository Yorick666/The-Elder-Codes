//
// Created by Yorick on 18/10/2016.
//

#ifndef THE_ELDER_CODES_DM_H
#define THE_ELDER_CODES_DM_H


class DM {
    DM();

    static DM *_instance;

public:
    static DM *getInstance();

    ~DM();
};

#endif //THE_ELDER_CODES_DM_H
