#include <random>
#include "Zvire.h"
#include "Prostredi.h"
using namespace std;

void Zvire::pohyb()
{
    x = max(0, min(prostredi->sirka - 1, x + rand() % 3 - 1));
    y = max(0, min(prostredi->vyska - 1, y + rand() % 3 - 1));
}

void Zvire::metabolismus() {
    energie -= 2;
}
