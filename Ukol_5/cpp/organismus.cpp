#include "organismus.h"


Organismus::Organismus(int x, int y, Prostredi *prostredi)
{
    this->x = x;
    this->y = y;
    this->prostredi = prostredi;
}
bool Organismus::jeZivy()
{
    return energie > 0;
}


