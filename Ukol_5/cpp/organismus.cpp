#include "organismus.h"
#include "prostredi.h"

Organismus::Organismus(int x, int y, Prostredi *prostredi) : x(x), y(y), prostredi(prostredi) {}

void Organismus::pohyb()
{

}

void Organismus::rozmnozovani()
{

}

void Organismus::metabolismus()
{

}

void Organismus::konzumuj(Organismus *other)
{

}

bool Organismus::JeZivy()
{
    return energie > 0;
}

char Organismus::getType() const
{
    return 'o';
}