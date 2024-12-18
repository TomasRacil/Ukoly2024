#include "prostredi.h"
#include "organismus.h"
#include <iostream>


Prostredi::Prostredi(int vyska, int sirka)
{
    this->vyska = vyska;
    this->sirka = sirka;
}

void Prostredi::krok()
{
    for (auto it = organismy.begin(); it != organismy.end();)
        {
            (*it)->pohyb();
            (*it)->metabolismus();
            (*it)->rozmnozovani();

            for (auto it2 = organismy.begin(); it2 != organismy.end(); ++it2)
            {
                if (it != it2 && (*it)->x == (*it2)->x && (*it)->y == (*it2)->y)
                {
                    (*it)->konzumuj(*it2);
                }
            }

            if (!(*it)->jeZivy())
            {
                it = organismy.erase(it);
            }
            else
            {
                ++it;
            }
        }
}
void Prostredi::odeberOrganismus(Organismus *o)
    {
        organismy.remove(o);
    }
void Prostredi::vypisStav()
{
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
}