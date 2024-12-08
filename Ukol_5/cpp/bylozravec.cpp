#include "bylozravec.h"
#include "prostredi.h"
#include <cstdlib>

Bylozravec::Bylozravec(int x, int y, Prostredi* prostredi)
    : Zvire(x, y, prostredi) {
    energie = 100;
}

void Bylozravec::rozmnozovani() {
    if (energie > 300) {
        for (int i = 0; i < rand() % 4; ++i) {
            prostredi->pridejOrganismus<Bylozravec>(x, y);
            energie /= 2;
        }
    }
}

void Bylozravec::konzumuj(Organismus* other) {
    if (other->getTyp() == 'R' && energie > other->energie) {
        energie += other->energie;
        other->energie = 0;
    }
}

char Bylozravec::getTyp() const {
    return 'B';
}
