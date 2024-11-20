
#include "Prostredi.h"
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

template <typename T>
void Prostredi::pridejOrganismus() {
    T* organismus = new T(rand() % sirka, rand() % vyska, this);
    organismy.push_back(organismus);
}

template <typename T>
void Prostredi::pridejOrganismus(int x, int y) {
    T* organismus = new T(x, y, this);
    organismy.push_back(organismus);
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