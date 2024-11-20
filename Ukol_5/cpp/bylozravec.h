//
// Created by danda on 18.11.2024.
//

#ifndef HEADERS_BYLOZRAVEC_H
#define HEADERS_BYLOZRAVEC_H

#include "zvire.h"
#include "prostredi.h"

class Bylozravec : public Zvire
{
public:
    Bylozravec(int x, int y, Prostredi *prostredi) : Zvire(x, y, prostredi)
    {
        energie = 100;
    }

    void konzumuj(Organismus *other) override
    {
        if (other->getTyp() == 'R' && energie > other->energie)
        {
            energie += other->energie;
            other->energie = 0;
        }
    }
    void rozmnozovani() override;
    char getTyp() override { return 'B'; }
};

#endif //HEADERS_BYLOZRAVEC_H
