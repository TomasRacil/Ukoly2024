#ifndef MASOZRAVEC_H
#define MASOZRAVEC_H

#include "zvire.h"

class Prostredi;

class Masozravec : public Zvire
{
public:
    Masozravec(int x, int y, Prostredi* prostredi);

    void konzumuj(Organismus* other) override;
    void rozmnozovani() override;
    char getTyp() override;
};


#endif 