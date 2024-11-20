#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <list>
#include <iostream>
#include <algorithm>
#include <cstdlib>

class Organismus;

class Prostredi
{
public:
    Prostredi(int vyska, int sirka);

    void krok();
    template <typename T>
    void pridejOrganismus();
    template <typename T>
    void pridejOrganismus(int x, int y);
    void odeberOrganismus(Organismus* o);
    void vypisStav();

private:
    int vyska, sirka;
    std::list<Organismus*> organismy;
};

#include "prostredi.cpp"

#endif // PROSTREDI_H
