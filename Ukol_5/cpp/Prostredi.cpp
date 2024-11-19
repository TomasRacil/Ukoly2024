#include <random>
#include <vector>
#include <iostream>
#include "Prostredi.h"


    Prostredi::Prostredi(int vyska, int sirka)
        : vyska(vyska), sirka(sirka) {}

    void Prostredi:: krok()
    {

        for (Organismus* o : organismy)
        {
            o->pohyb();
            o->metabolismus();
            o->rozmnozovani();
        }

        for (Organismus* o1 : organismy)
        {
            for (Organismus* o2 : organismy)
            {
                if (o1 != o2 && o1->x == o2->x && o1->y == o2->y)
                {
                    o1->konzumuj(o2);
                }
            }
        }

        organismy.remove_if([](Organismus* o)
            { return !o->jeZivy(); });

        
    }

    
    

    void Prostredi:: odeberOrganismus(Organismus* o)
    {
        organismy.remove(o);
    }

    void Prostredi:: vypisStav()
    {
        int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
        for (Organismus* o : organismy)
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
            cout << "Rostliny: " << pocetRostlin
            << ", Bylozravci: " << pocetBylozravcu
            << ", Masozravci: " << pocetMasozravcu << std::endl;
    }