#ifndef MASOZRAVEC_H
#define MASOZRAVEC_H
#include "zvire.h"

class Masozravec : public Zvire
{
    Masozravec(int x, int y, Prostredi *prostredi);

    void konzumuj(Organismus *other);
    void rozmnozovani();
    char getType() const;
};

#endif