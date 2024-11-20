
#ifndef PROSTREDI_H
#define PROSTREDI_H

#include "Organismus.h"
#include <list>

class Prostredi {
public:
    int vyska, sirka;
    std::list<Organismus*> organismy;

    Prostredi(int vyska, int sirka);
    ~Prostredi();

    void krok();
    template <typename T> void pridejOrganismus();
    template <typename T> void pridejOrganismus(int x, int y);
    void vypisStav();
};

#endif // PROSTREDI_H
