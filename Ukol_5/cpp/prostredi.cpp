#include "prostredi.h"
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"
#include <iostream>

Prostredi::Prostredi(int vyska, int sirka) : vyska(vyska), sirka(sirka) {}

Prostredi::~Prostredi() {
    for (Organismus *o : organismy) {
        delete o;
    }
}

void Prostredi::vypisStav() {
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
    for (Organismus *o : organismy) {
        switch (o->getTyp()) {
            case 'R': pocetRostlin++; break;
            case 'B': pocetBylozravcu++; break;
            case 'M': pocetMasozravcu++; break;
        }
    }
    std::cout << "Rostliny: " << pocetRostlin << ", Bylozravci: " << pocetBylozravcu << ", Masozravci: " << pocetMasozravcu << std::endl;
}

void Prostredi::krok() {
    for (Organismus *o : organismy) {
        o->krok();
    }
    organismy.remove_if([](Organismus *o) {
        if (!o->jeZivy()) {
            delete o;
            return true;
        }
        return false;
    });
}

template <typename T>
void Prostredi::pridejOrganismus() {
    int x = rand() % sirka;
    int y = rand() % vyska;
    organismy.push_back(new T(x, y, this));
}

// Explicitní deklarace šablonových metod
template void Prostredi::pridejOrganismus<Rostlina>();
template void Prostredi::pridejOrganismus<Bylozravec>();
template void Prostredi::pridejOrganismus<Masozravec>();
