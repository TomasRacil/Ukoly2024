
#include "Prostredi.h"
#include "Rostlina.h"
#include "Bylozravec.h"
#include "Masozravec.h"
#include <iostream>
#include <random>

Prostredi::Prostredi(int vyska, int sirka) : vyska(vyska), sirka(sirka) {}
Prostredi::~Prostredi() {
    for (auto o : organismy)
        delete o;
}

void Prostredi::krok() {
    for (auto it = organismy.begin(); it != organismy.end();) {
        (*it)->pohyb();
        (*it)->metabolismus();
        (*it)->rozmnozovani();
        if (!(*it)->jeZivy()) {
            delete *it;
            it = organismy.erase(it);
        } else {
            ++it;
        }
    }
}



void Prostredi::vypisStav() {
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
    for (auto o : organismy) {
        switch (o->getTyp()) {
            case 'R': pocetRostlin++; break;
            case 'B': pocetBylozravcu++; break;
            case 'M': pocetMasozravcu++; break;
        }
    }
    std::cout << "Rostliny: " << pocetRostlin
              << ", Bylozravci: " << pocetBylozravcu
              << ", Masozravci: " << pocetMasozravcu << std::endl;
}