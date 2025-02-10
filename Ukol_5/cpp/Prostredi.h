#ifndef PROSTREDI_H
#define PROSTREDI_H

#include "Organismus.h"
#include <list>
#include <random>
using namespace std;

class Prostredi
{
public:
    int vyska, sirka;
    list<Organismus*> organismy;

    Prostredi(int vyska, int sirka);

    void krok();
    template <class T>
    void pridejOrganismus()
    {
        T* organismus = new T(rand() % sirka, rand() % vyska, this);
        organismy.push_back(organismus);
    }
    void odeberOrganismus(Organismus* o);
    void vypisStav();
       
};

#endif
