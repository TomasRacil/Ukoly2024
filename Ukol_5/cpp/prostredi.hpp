#ifndef PROSTREDI_H
#define PROSTREDI_H


#include <list>
#include <iostream>

//forward declaration to avoid cyclic reference
class Organismus;

class Prostredi
{
public:
    int vyska, sirka;
    std::list<Organismus *> organismy;
    Prostredi(int vyska, int sirka);

    void krok();

    //templates must be defined in the class:
    template <typename T>
    void pridejOrganismus()
    {
        T *organismus = new T(rand() % sirka, rand() % vyska, this);
        organismy.push_back(organismus);
    }

    template <typename T>
    void pridejOrganismus(int x, int y)
    {
        int new_position_x = std::max(0, std::min(sirka - 1, x));
        int new_position_y = std::max(0, std::min(vyska - 1, y));

        T *organismus = new T(new_position_x, new_position_y, this);
        organismy.push_back(organismus);
    }

    void odeberOrganismus(Organismus *o);
    void vypisStav();
    void apokalypsa();
};


#endif