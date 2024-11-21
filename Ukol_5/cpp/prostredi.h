#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <iostream>
#include <list>
#include <vector>
#include "organismus.h"

class Prostredi {
public:
    int vyska, sirka;
    std::list<Organismus *> organismy;

    Prostredi(int vyska, int sirka);

    ~Prostredi();

    void krok();

    void vypisStav();

    template<typename T>
    void pridejOrganismus();

    template<typename T>
    void pridejOrganismus(int x, int y);

    void odeberOrganismus(Organismus *o);
};

#include "prostredi_impl.h" // Include template definitions

#endif
