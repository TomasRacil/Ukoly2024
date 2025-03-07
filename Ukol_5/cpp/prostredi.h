#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <list>
#include <iostream>
#include <cstdlib>

class Organismus;

class Prostredi {
public:
    Prostredi(int vyska, int sirka);
    ~Prostredi();

    template <typename T>
    void pridejOrganismus() {
        int x = rand() % sirka;
        int y = rand() % vyska;
        T *novyOrganismus = new T(x, y, this);
        organismy.push_back(novyOrganismus);
    }

    template <typename T>
    void pridejOrganismus(int x, int y) {
        x = std::max(0, std::min(sirka - 1, x));
        y = std::max(0, std::min(vyska - 1, y));
        T *novyOrganismus = new T(x, y, this);
        organismy.push_back(novyOrganismus);
    }

    void krok();
    void vypisStav();

    int getSirka() const;
    int getVyska() const;

private:
    int vyska, sirka;
    std::list<Organismus *> organismy;
};

#endif
