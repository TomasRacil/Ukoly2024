#ifndef bylozravec_h
#define bylozravec_h
#include "zvire.h"

class Bylozravec : public Zvire
{
public:
    Bylozravec(int x, int y, Prostredi *prostredi);

    void rozmnozovani() override;
    void konzumuj(Organismus *other) override;
    char getTyp() override;
};











#endif // bylozravec_h