//
// Created by danda on 18.11.2024.
//

#ifndef HEADERS_MASOZRAVEC_H
#define HEADERS_MASOZRAVEC_H

#include "zvire.h"

class Masozravec : public Zvire
{
public:
    Masozravec(int x, int y, Prostredi *prostredi) : Zvire(x, y, prostredi)
    {
        energie = 200;
    }

    void konzumuj(Organismus *other) override
    {
        if (other->getTyp() == 'B' && energie > other->energie)
        {
            energie += other->energie;
            other->energie = 0;
        }
    }
    void rozmnozovani() override;
    char getTyp() override { return 'M'; }
};

#endif //HEADERS_MASOZRAVEC_H
