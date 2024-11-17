#ifndef ROSTLINA_H
#define ROSTLINA_H
#include "organismus.h"

class Rostlina : public Organismus
{
    public:
    Rostlina(int x, int y, Prostredi *prostredi);
    void pohyb();
    void metabolismus();
    void rozmnozovani();
    void konzumuj(Organismus *other);
    char getType() const;
};


#endif