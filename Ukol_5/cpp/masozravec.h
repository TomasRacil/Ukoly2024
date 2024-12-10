#ifndef MASOZRAVEC_H
#define MASOZRAVEC_H

#include "zvire.h"

class Masozravec : public Zvire {
public:
    Masozravec(int x, int y, Prostredi* prostredi);
    void rozmnozovani() override;
    void konzumuj(Organismus* other) override;
    char getTyp() const override;
};

#endif // MASOZRAVEC_H
