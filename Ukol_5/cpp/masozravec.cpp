#include "masozravec.h"

Masozravec::Masozravec(int x, int y, Prostredi *prostredi) : Zvire(x,y,prostredi)
{
    energie = 200;
}

void Masozravec ::konzumuj(Organismus *other)
{
    if(other->getType() == 'B' && energie > other->energie)
    {
        energie += other->energie;
        other->energie = 0;
    }
}

void Masozravec ::rozmnozovani()
{
    if(energie > 500)
    {
        int pocetPotomku = rand() % 2;
        for(int i = 0; i < pocetPotomku; i++)
        {
            prostredi->pridejOrganismus<Masozravec>(x,y);
            energie /= 2;
        }
    }
}

char Masozravec::getType() const
{
    return 'M';
}