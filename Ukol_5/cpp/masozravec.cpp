#include "masozravec.h"
#include "prostredi.h"
#include <cstdlib>  // Pro rand()

Masozravec::Masozravec(int x, int y, Prostredi* prostredi)
    : Zvire(x, y, prostredi)
{
    energie=200;
}

void Masozravec::rozmnozovani() {
    if (energie > 500) {
        int pocetPotomku = rand() % 2; // Počet potomků uložen do proměnné

        for (int i = 0; i < pocetPotomku; ++i) {
            prostredi->pridejOrganismus<Masozravec>(x, y);
            energie /= 2;
        }
    }
}

void Masozravec::konzumuj(Organismus* other) {
    if (other->getTyp() == 'B' && energie > other->energie) {
        energie += other->energie;
        other->energie = 0;
    }
}

char Masozravec::getTyp() const {
    return 'M';
}
