#ifndef zvire_h
#define zvire_h
#include "organismus.h"

class Zvire : public Organismus
{
public:
    Zvire(int x, int y, Prostredi *prostredi);
    void pohyb() override;
    void metabolismus() override;
    void rozmnozovani() = 0;
    void konzumuj(Organismus *other) = 0;
};

#endif // zvire_h