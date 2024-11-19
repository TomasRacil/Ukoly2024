#ifndef BYLOZRAVEC_H
#define BYLOZRAVEC_H

#include "zvire.hpp"

#include <random>

class Bylozravec : public Zvire {
public:
    Bylozravec(int x, int y, Prostredi *prostredi);

    void konzumuj(Organismus *other) override;
    void rozmnozovani() override;
    char getTyp() override;
};

#endif