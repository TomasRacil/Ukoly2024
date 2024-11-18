//
// Created by Jakub Václav Flasar on 18.11.2024.
//

#ifndef UKOL_5_ZVIRE_H
#define UKOL_5_ZVIRE_H

#include "organismus.h"

class Zvire : public Organismus
{
public:
    Zvire(int x, int y, Prostredi *prostredi) : Organismus(x, y, prostredi) {}

    void pohyb() override;
    void metabolismus() override;
    virtual void rozmnozovani() = 0;
    virtual void konzumuj(Organismus *other) = 0;
};

#endif //UKOL_5_ZVIRE_H
