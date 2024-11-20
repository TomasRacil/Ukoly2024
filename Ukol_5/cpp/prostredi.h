#ifndef PROSTREDI_H
#define PROSTREDI_H
#include <list>
#include <vector>
#include <random>
#include <iostream>
#include "organismus.h"

using namespace std;

class Organismus;
class Prostredi
{
    public:
    int vyska, sirka;
    list<Organismus *> organismy;

    Prostredi(int vyska, int sirka);
    void krok();
    template<typename T>
    void pridejOrganismus()
    {
        T *organismus = new T(rand()%sirka, rand()%vyska,this);
        organismy.push_back(organismus);
    }
    template <typename T>
    void pridejOrganismus(int x, int y)
    {
        int new_position_x = max(0, min(sirka - 1, x));
        int new_position_y = max(0, min(vyska - 1, y));

        T *organismus = new T(new_position_x, new_position_y, this);
        organismy.push_back(organismus);
    }
    void odeberOrganismus(Organismus *o);
    void vypisStav();
};

#endif