#include "prostredi.h"
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

//konstruktor prostředí
Prostredi::Prostredi(int vyska, int sirka)
    : vyska(vyska), sirka(sirka) {}

//destruktor prostředí
Prostredi::~Prostredi() {
    for (Organismus* o : organismy) {
        delete o;
    }
    organismy.clear();
}

//jednotlivý krok simulace
void Prostredi::krok() {
    // Každý organismus vykoná své akce
    for (Organismus* o : organismy) {
        o->pohyb();
        o->metabolismus();
        o->rozmnozovani();
    }

    //kontroluj e jejich interakce
    for (auto it1 = organismy.begin(); it1 != organismy.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != organismy.end(); ++it2) {
            Organismus* o1 = *it1;
            Organismus* o2 = *it2;
            if (o1->getX() == o2->getX() && o1->getY() == o2->getY()) {
                o1->konzumuj(o2);
            }
        }
    }

    //odstraní mrtvé 
    organismy.remove_if([](Organismus* o) {
        if (!o->jeZivy()) {
            delete o;
            return true;
        }
        return false;
    });
}

//přidání organismu na náhodnou pozici
template <typename T>
void Prostredi::pridejOrganismus() {
    pridejOrganismus<T>(rand() % sirka, rand() % vyska);
}

//přidání organismu na konkrétní pozici
template <typename T>
void Prostredi::pridejOrganismus(int x, int y) {
    x = std::clamp(x, 0, sirka - 1);
    y = std::clamp(y, 0, vyska - 1);
    organismy.push_back(new T(x, y, this));
}

//odebrání organismu ze seznamu (kontroluje, zda existuje)
void Prostredi::odeberOrganismus(Organismus* o) {
    if (o) {
        organismy.remove(o);
        delete o;
    }
}

//vypisuje momentální stav prostredi
void Prostredi::vypisStav() const {
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;

    for (const Organismus* o : organismy) {
        switch (o->getTyp()) {
            case 'R': ++pocetRostlin; break;
            case 'B': ++pocetBylozravcu; break;
            case 'M': ++pocetMasozravcu; break;
        }
    }

    std::cout << "Rostliny: " << pocetRostlin
              << ", Bylozravci: " << pocetBylozravcu
              << ", Masozravci: " << pocetMasozravcu << std::endl;
}

//definice šablon-metod
template void Prostredi::pridejOrganismus<Rostlina>();
template void Prostredi::pridejOrganismus<Bylozravec>();
template void Prostredi::pridejOrganismus<Masozravec>();

template void Prostredi::pridejOrganismus<Rostlina>(int, int);
template void Prostredi::pridejOrganismus<Bylozravec>(int, int);
template void Prostredi::pridejOrganismus<Masozravec>(int, int);
