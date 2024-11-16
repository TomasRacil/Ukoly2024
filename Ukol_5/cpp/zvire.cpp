#include "zvire.hpp"
#include "prostredi.hpp"

Zvire::Zvire(int x, int y, Prostredi *prostredi) : Organismus(x, y, prostredi) {}


void Zvire::metabolismus()
{
    energie -= 2;
}

void Zvire::pohyb()
{
    x = std::max(0, std::min(prostredi->sirka - 1, x + rand() % 3 - 1));
    y = std::max(0, std::min(prostredi->vyska - 1, y + rand() % 3 - 1));
}