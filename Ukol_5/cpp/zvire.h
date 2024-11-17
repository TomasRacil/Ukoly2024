#ifndef ZVIRE_H
#define ZVIRE_H
#include "organismus.h"

class Zvire : public Organismus
{
    public:
    Zvire(int x, int y, Prostredi *prostredi);
    void pohyb();
    void metabolismus();
    void rozmnozovani();
    void konzumuj(Organismus *other);

};

#endif
