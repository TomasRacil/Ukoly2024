#ifndef UKOL_5_ROSTLINA_H
#define UKOL_5_ROSTLINA_H

#include "organismus.h"
class Prostredi;

class Rostlina : public Organismus
{
public:
    Rostlina(int x, int y, Prostredi *prostredi);

    void pohyb() override;

    void metabolismus() override;

    void rozmnozovani() override;

    void konzumuj(Organismus *other) override;
    char getTyp() override;
};

#endif
