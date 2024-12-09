#ifndef UKOL_5_BYLOZRAVEC_H
#define UKOL_5_BYLOZRAVEC_H

#include "zvire.h"

class Bylozravec : public Zvire
{
public:
    Bylozravec(int x, int y, Prostredi *prostredi);

    void konzumuj(Organismus *other) override;
    void rozmnozovani() override;
    char getTyp() override;
};


#endif
