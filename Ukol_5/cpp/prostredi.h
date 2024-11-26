#ifndef UKOL_5_PROSTREDI_H
#define UKOL_5_PROSTREDI_H

#include "organismus.h"
#include <random>
#include <list>
#include <vector>
#include <iostream>

class Prostredi
{
public:
    int vyska, sirka;
    std::list<Organismus *> organismy;

    Prostredi(int vyska, int sirka) : vyska(vyska), sirka(sirka) {}

    void krok()
    {

        for (Organismus *o : organismy)
        {
            o->pohyb();
            o->metabolismus();
            o->rozmnozovani();
        }

        for (Organismus *o1 : organismy)
        {
            for (Organismus *o2 : organismy)
            {
                if (o1 != o2 && o1->x == o2->x && o1->y == o2->y)
                {
                    o1->konzumuj(o2);
                }
            }
        }

        organismy.remove_if([](Organismus *o)
                            { return !o->jeZivy(); });
    }

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

    void odeberOrganismus(Organismus *o)
    {
        organismy.remove(o);
    }

    void vypisStav()
    {
        int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
        for (Organismus *o : organismy)
        {
            switch (o->getTyp())
            {
                case 'R':
                    pocetRostlin++;
                    break;
                case 'B':
                    pocetBylozravcu++;
                    break;
                case 'M':
                    pocetMasozravcu++;
                    break;
            }
        }
        std::cout << "Rostliny: " << pocetRostlin
                  << ", Bylozravci: " << pocetBylozravcu
                  << ", Masozravci: " << pocetMasozravcu << std::endl;
    }
};

#endif
