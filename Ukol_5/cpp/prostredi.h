#ifndef PROSTREDI_H
#define PROSTREDI_H
#include <list>
#include <vector>
#include <random>
#include <iostream>

using namespace std;

class Organismus;
class Prostredi
{
    public:
    int vyska, sirka;
    list<Organismus *>organismy;

    Prostredi(int vyska, int sirka);
    void krok();
    template<typename T>
    void pridejOrganismus();
    template <typename T>
    void pridejOrganismus(int x, int y);
    void odeberOrganismus(Organismus *o);
    void vypisStav();
};

#endif