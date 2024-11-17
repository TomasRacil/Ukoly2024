#ifndef BYLOZRAVEC_H
#define BYLOZRAVEC_H


#include <random>

#include "zvire.hpp"

class Bylozravec : public Zvire {
public:
    Bylozravec(int x, int y, Prostredi *prostredi);
    ~Bylozravec() {};

    void konzumuj(Organismus *other) override;
    void rozmnozovani() override;
    char getTyp() override;
};

#endif