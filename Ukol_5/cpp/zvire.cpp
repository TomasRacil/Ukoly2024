#include "zvire.h"

using namespace std;

Zvire ::Zvire(int x, int y, Prostredi *prostredi) : Organismus(x,y,prostredi) {}

void Zvire ::pohyb()
{
    x = max(0, min(prostredi->sirka - 1, x + rand() % 3 - 1));
    y = max(0, min(prostredi->vyska - 1, y + rand() % 3 - 1));
}

void Zvire::metabolismus()
{
    energie -= 2;
}

void Zvire :: rozmnozovani()
{

}

void konzumuj(Organismus *other)
{
    
}