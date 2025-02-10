#include "Rostlina.h"
#include "Prostredi.h"

void Rostlina::rozmnozovani()
{
    if (energie > 30)
    {
        int pocetPotomku = rand() % 10;

        for (int i = 0; i < pocetPotomku; ++i)
        {
            prostredi->pridejOrganismus<Rostlina>();
            energie /= 2;
        }
    }
}

char Rostlina::getTyp() { return 'R'; }

void Rostlina::metabolismus() {
    energie += 1;
}

Rostlina::Rostlina(int x, int y, Prostredi* prostredi) : Organismus(x, y, prostredi)
{
    energie = 10;
}

void Rostlina::konzumuj(Organismus* other) {}

void Rostlina::pohyb() {}
