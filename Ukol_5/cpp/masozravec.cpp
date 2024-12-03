#include "masozravec.h"
#include "prostredi.h"
#include "organismus.h"
#include <random>

Masozravec::Masozravec(int x, int y, Prostredi *prostredi) : Zvire(x, y, prostredi) 
{
    energie = 200;
}
void Masozravec::konzumuj(Organismus *other)
{
    if (other->getTyp() == 'B')
    {
        energie += other->energie;
        other->energie = 0;
    }
}
char Masozravec::getTyp() 
{
     return 'M' ;
}

void Masozravec::rozmnozovani()
{
    if (energie > 500)
    {
        int pocetPotomku = rand() % 4;

        for (int i = 0; i < pocetPotomku; ++i)
        {
            prostredi->Prostredi::pridejOrganismus<Masozravec>(x, y);
            energie /= 2;
        }
    
}
}