#include "prostredi.h"
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

// Konstruktor prostředí
Prostredi::Prostredi(int vyska, int sirka)
    : vyska(vyska), sirka(sirka) {}

// Destruktor prostředí
Prostredi::~Prostredi() {
    for (Organismus* o : organismy) {
        delete o;
    }
    organismy.clear();
}

// Jednotlivý krok simulace
void Prostredi::krok() {
    // Každý organismus vykoná své akce
    for (Organismus* o : organismy) {
        o->pohyb();
        o->metabolismus();
        o->rozmnozovani();
    }

    // Kontrola kolizí a interakcí
    for (Organismus* o1 : organismy) {
        for (Organismus* o2 : organismy) {
            if (o1 != o2 && o1->x == o2->x && o1->y == o2->y) {
                o1->konzumuj(o2);
            }
        }
    }

    // Odstranění mrtvých organismů
    organismy.remove_if([](Organismus* o) {
        bool dead = !o->jeZivy();
        if (dead) delete o;
        return dead;
    });
}

// Přidání organismu na náhodnou pozici
template <typename T>
void Prostredi::pridejOrganismus() {
    int x = rand() % sirka;
    int y = rand() % vyska;
    T* organismus = new T(x, y, this);
    organismy.push_back(organismus);
}

// Přidání organismu na konkrétní pozici
template <typename T>
void Prostredi::pridejOrganismus(int x, int y) {
    int new_x = std::clamp(x, 0, sirka - 1);
    int new_y = std::clamp(y, 0, vyska - 1);
    T* organismus = new T(new_x, new_y, this);
    organismy.push_back(organismus);
}

// Odebrání organismu ze seznamu
void Prostredi::odeberOrganismus(Organismus* o) {
    organismy.remove(o);
    delete o;
}

// Výpis aktuálního stavu prostředí
void Prostredi::vypisStav() {
    int pocetRostlin = 0, pocetBylozravcu = 0, pocetMasozravcu = 0;
    for (Organismus* o : organismy) {
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

// Explicitní definice šablonových metod
template void Prostredi::pridejOrganismus<Rostlina>();
template void Prostredi::pridejOrganismus<Bylozravec>();
template void Prostredi::pridejOrganismus<Masozravec>();

template void Prostredi::pridejOrganismus<Rostlina>(int, int);
template void Prostredi::pridejOrganismus<Bylozravec>(int, int);
template void Prostredi::pridejOrganismus<Masozravec>(int, int);
