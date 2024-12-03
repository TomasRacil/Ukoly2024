#include "rostlina.h"
#include "organismus.h"
#include "prostredi.h"

Rostlina::Rostlina(int x, int y, Prostredi *prostredi) : Organismus(x, y, prostredi) 
{
    energie = 10;
}

void Rostlina::metabolismus()
{
    energie += 1;
}

char Rostlina::getTyp() 
{
    return 'R';
}
void Rostlina::pohyb(){}
void Rostlina::rozmnozovani(){}
void Rostlina::konzumuj(Organismus *other){}


