#include "Bylozravec.h"
#include "Prostredi.h"
#include <random>

void Bylozravec::rozmnozovani()
{
    if (energie > 300)
    {
        int pocetPotomku = rand() % 4;

        for (int i = 0; i < pocetPotomku; ++i)
        {
            prostredi->pridejOrganismus<Bylozravec>();
            energie /= 2;
        }
    }
}

Bylozravec::Bylozravec(int x, int y, Prostredi* prostredi) : Zvire(x, y, prostredi)
{
    energie = 100;
}

char Bylozravec::getTyp() { return 'B'; }

void Bylozravec::konzumuj(Organismus* other) {
    if (other->getTyp() == 'R' && energie > other->energie)
    {
        energie += other->energie;
        other->energie = 0;
    }
}
