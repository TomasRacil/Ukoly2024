#include <iostream>
#include "prostredi.h"
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"

int main() {
    // Vytvoření prostředí 20x20 (xy)
    Prostredi prostredi(20, 20);

    
    for (int i = 0; i < 8; ++i) {
        prostredi.pridejOrganismus<Rostlina>();
    }
    
    for (int i = 0; i < 2; ++i) {
        prostredi.pridejOrganismus<Masozravec>();
    }
    
   
    for (int i = 0; i < 4; ++i) {
        prostredi.pridejOrganismus<Bylozravec>();
    }

    

    
    std::cout << "Počáteční stav prostředí:" << std::endl;
    prostredi.vypisStav();

    //krokování
    int pocetKroku = 50;
    for (int i = 0; i < pocetKroku; ++i) {
        std::cout << "Krok " << i + 1 << ":" << std::endl;
        prostredi.krok();        // Proveď jeden krok simulace
        prostredi.vypisStav();   // Vypiš stav prostředí
    }

    return 0;
}
