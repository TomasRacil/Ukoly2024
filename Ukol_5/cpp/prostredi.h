#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <list>
#include "organismus.h"

class Prostredi {
public:
    int vyska, sirka;
    std::list<Organismus*> organismy;

    Prostredi(int vyska, int sirka);
    ~Prostredi();

    void krok();
    template <typename T> void pridejOrganismus();
    template <typename T> void pridejOrganismus(int x, int y);
    void odeberOrganismus(Organismus* o);
    void vypisStav() const;
};

#endif // PROSTREDI_H
