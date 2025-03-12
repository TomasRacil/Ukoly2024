#ifndef BYLOZRAVEC_H
#define BYLOZRAVEC_H

#include "zvire.h"

class Bylozravec : public Zvire 
{
public:
    Bylozravec(int x, int y, Prostredi* prostredi);
    void rozmnozovani() override;
    void konzumuj(Organismus* other) override;
    char getTyp() const override;
};

#endif // BYLOZRAVEC_H
