#include "rostlina.hpp"

Rostlina::Rostlina(int x, int y, Prostredi *prostredi) : Organismus(x, y, prostredi) {
    energie = 10;
}

void Rostlina::metabolismus() {
    ++energie;
}

void Rostlina::rozmnozovani() {
    if (energie > 30) {
        int pocetPotomku = rand() % 10;

        for (int i = 0; i < pocetPotomku; ++i) {
            prostredi->pridejOrganismus<Rostlina>();
            energie /= 2;
        }
    }
}

char Rostlina::getTyp() {
    return 'R';
}