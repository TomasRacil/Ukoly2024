#include "bylozravec.h"
#include "prostredi.h"
#include "organismus.h"
#include <random>

Bylozravec::Bylozravec(int x, int y, Prostredi *prostredi) : Zvire(x, y, prostredi) 
{
    energie = 100;
}
void Bylozravec::konzumuj(Organismus *other)
{
    if (other->getTyp() == 'R')
    {
        energie += other->energie;
        other->energie = 0;
    }
}
char Bylozravec::getTyp() 
{
     return 'B' ;
}
void Bylozravec::rozmnozovani()
{
    if (energie > 300)
    {
        int pocetPotomku = rand() % 4;

        for (int i = 0; i < pocetPotomku; ++i)
        {
            prostredi->Prostredi::pridejOrganismus<Bylozravec>(x, y);
            energie /= 2;
        }
    
}
}