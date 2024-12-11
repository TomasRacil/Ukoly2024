#include "prostredi.h"
#include "organismus.h"
#include <cstdlib>

Prostredi::Prostredi(int vyska, int sirka)
        : vyska(vyska), sirka(sirka) {}

Prostredi::~Prostredi() {
    for (Organismus *organismus : organismy) {
        delete organismus;
    }
}

void Prostredi::krok() {
    for (Organismus *organismus : organismy) {
        organismus->pohyb();
        organismus->metabolismus();
        organismus->rozmnozovani();
    }

    for (Organismus *o1 : organismy) {
        for (Organismus *o2 : organismy) {
            if (o1 != o2 && o1->x == o2->x && o1->y == o2->y) {
                o1->konzumuj(o2);
            }
        }
    }

    organismy.remove_if([](Organismus *organismus) {
        return !organismus->jeZivy();
    });
}

void Prostredi::vypisStav() {
    int pocetRostlin = 0, pocetBylozravec = 0, pocetMasozravec = 0;

    for (Organismus *organismus : organismy) {
        switch (organismus->getTyp()) {
            case 'R':
                pocetRostlin++;
                break;
            case 'B':
                pocetBylozravec++;
                break;
            case 'M':
                pocetMasozravec++;
                break;
        }
    }

    std::cout << "Rostliny: " << pocetRostlin
              << ", Bylozravci: " << pocetBylozravec
              << ", Masozravci: " << pocetMasozravec << std::endl;
}

// Implementace getter metod
int Prostredi::getSirka() const {
    return sirka;
}

int Prostredi::getVyska() const {
    return vyska;
}
