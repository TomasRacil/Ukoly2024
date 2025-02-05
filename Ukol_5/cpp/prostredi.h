#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "organismus.h"

class Prostredi {
    int sirka, vyska;
    std::vector<Organismus*> organismy;

public:
    Prostredi(int sirka, int vyska) : sirka(sirka), vyska(vyska) {
        srand(static_cast<unsigned>(time(0))); 
    }

    ~Prostredi() {
        for (Organismus* o : organismy) {
            delete o;
        }
    }

    void pridatOrganismus(Organismus* organismus) {
        organismy.push_back(organismus);
    }

    void vykresli() const {
        for (Organismus* o : organismy) {
            std::cout << o->getTyp() << " na (" << o->getX() << ", " << o->getY() << ")\n";
        }
        std::cout << "--------------------------\n";
    }

    void simuluj(int kroky) {
        for (int i = 0; i < kroky; ++i) {
            std::cout << "Krok " << i + 1 << ":\n";
            for (Organismus* o : organismy) {
                if (o->isAlive()) {
                    o->pohyb(sirka, vyska);
                    o->zmensiZivotnost();
                }
            }
            vykresli();
        }
    }
};
#endif