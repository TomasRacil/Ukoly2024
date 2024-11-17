#include "prostredi.h"
#include "organismus.h"


Prostredi::Prostredi(int vyska, int sirka) : vyska(vyska), sirka(sirka) {}

void Prostredi :: krok()
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
                            { return !o->JeZivy(); });
}
template <typename T>
void Prostredi ::pridejOrganismus()
{
    T *organismus = new T(rand()%sirka, rand()%vyska,this);
    organismy.push_back(organismus);
}

template <typename T>
void Prostredi::pridejOrganismus(int x, int y)
{
    int new_position_x = max(0, min(sirka - 1, x));
    int new_position_y = max(0, min(vyska - 1, y));

    T *organismus = new T(new_position_x, new_position_y, this);
    organismy.push_back(organismus);
}

void Prostredi :: odeberOrganismus(Organismus *o)
{
    organismy.remove(o);
}

void Prostredi :: vypisStav()
{
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
        for (Organismus *o : organismy)
        {
            switch (o->getType())
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
         << ", Masozravci: " << pocetMasozravcu << endl;
}