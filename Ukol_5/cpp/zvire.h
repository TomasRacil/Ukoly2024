//
// Created by danda on 18.11.2024.
//

#ifndef HEADERS_ZVIRE_H
#define HEADERS_ZVIRE_H

#include "organismus.h"

class Zvire : public Organismus
{
public:
    Zvire(int x, int y, Prostredi *prostredi) : Organismus(x, y, prostredi) {}

    void pohyb() override;
    void metabolismus() override
    {
        energie -= 2;
    }
    virtual void rozmnozovani() = 0;
    virtual void konzumuj(Organismus *other) = 0;
};

#endif //HEADERS_ZVIRE_H
