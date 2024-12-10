#include <iostream>
#include "prostredi.h"
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"

int main() {
    // Vytvoření prostředí s rozměry 20x20
    Prostredi prostredi(20, 20);

    // Přidání rostlin
    for (int i = 0; i < 8; ++i) {
        prostredi.pridejOrganismus<Rostlina>();
    }

    // Přidání býložravců
    for (int i = 0; i < 4; ++i) {
        prostredi.pridejOrganismus<Bylozravec>();
    }

    // Přidání masožravců
    for (int i = 0; i < 2; ++i) {
        prostredi.pridejOrganismus<Masozravec>();
    }

    // Výpis počátečního stavu
    std::cout << "Počáteční stav prostředí:" << std::endl;
    prostredi.vypisStav();

    // Simulace kroků
    int pocetKroku = 50;
    for (int i = 0; i < pocetKroku; ++i) {
        std::cout << "Krok " << i + 1 << ":" << std::endl;
        prostredi.krok();        // Proveď jeden krok simulace
        prostredi.vypisStav();   // Vypiš stav prostředí
    }

    return 0;
}