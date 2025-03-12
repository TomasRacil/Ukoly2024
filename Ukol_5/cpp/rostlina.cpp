#include "rostlina.h"
#include "prostredi.h"
#include <cstdlib>

//Rostlina::Rostlina(int x, int y, Prostredi* prostredi)
  //  : Organismus(x, y, prostredi), energie(10) {}

//void Rostlina::pohyb() {}

void Rostlina::metabolismus() {
    ++energie;
}

void Rostlina::rozmnozovani() {
    if (energie > 30) {
        for (int i = 0; i < rand() % 10; ++i) {
            prostredi->pridejOrganismus<Rostlina>();
        }
        energie /= 2;
    }
}

/*void Rostlina::konzumuj(Organismus*) {}

char Rostlina::getTyp() const {
    return 'R';
}*/
