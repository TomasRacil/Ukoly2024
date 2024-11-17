#include "rostlina.h"
#include "prostredi.h"

Rostlina::Rostlina(int x, int y, Prostredi *prostredi) : Organismus(x,y,prostredi) 
{
    energie = 10;
}

void Rostlina ::pohyb() 
{
    
}

void Rostlina ::metabolismus()
{
    energie += 1;
}

void Rostlina ::rozmnozovani()
{
    if(energie > 30)
    {
        int pocetPotomku = rand() % 10;
        for(int i = 0; i < pocetPotomku; i++)
        {
            prostredi->pridejOrganismus<Rostlina>();
            energie /= 2;
        }
    }
}

void Rostlina ::konzumuj(Organismus *other)
{

}

char Rostlina :: getType() const
{
    return 'R';
}