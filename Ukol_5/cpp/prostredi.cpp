#include "prostredi.h"
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"
#include <iostream>
#include <algorithm>

// Konstruktor
Prostredi::Prostredi(int vyska, int sirka) : vyska(vyska), sirka(sirka) {}

// Destruktor
Prostredi::~Prostredi() {
    for (auto organismus: organismy) {
        delete organismus;
    }
}

// Metoda pro výpis stavu
void Prostredi::vypisStav() {
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
    for (Organismus *o: organismy) {
        switch (o->getTyp()) {
            case 'R':
                pocetRostlin++;
                break;
            case 'B':
                pocetBylozravcu++;
                break;
            case 'M':
                pocetMasozravcu++;
                break;
        }
    }
    std::cout << "Rostliny: " << pocetRostlin << ", Bylozravci: " << pocetBylozravcu << ", Masozravci: "
              << pocetMasozravcu << std::endl;
}

// Metoda pro krok simulace
void Prostredi::krok() {
    for (Organismus *o: organismy) {
        o->pohyb();
        o->metabolismus();
        o->rozmnozovani();
    }
    organismy.remove_if([](Organismus *o) { return !o->jeZivy(); });
}


void Prostredi::vypisStav() {
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
    for (Organismus *o: organismy) {
        switch (o->getTyp()) {
            case 'R':
                pocetRostlin++;
                break;
            case 'B':
                pocetBylozravcu++;
                break;
            case 'M':
                pocetMasozravcu++;
                break;
        }
    }
    std::cout << "Rostliny: " << pocetRostlin
              << ", Bylozravci: " << pocetBylozravcu
              << ", Masozravci: " << pocetMasozravcu << std::endl;
}
