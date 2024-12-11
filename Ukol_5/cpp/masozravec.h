#ifndef masozravec_h
#define masozravec_h
#include "zvire.h"

class Masozravec : public Zvire
{
public:
    Masozravec(int x, int y, Prostredi *prostredi);

    void rozmnozovani() override;
    void konzumuj(Organismus *other) override;
    char getTyp() override;
};





#endif // masozravec_h