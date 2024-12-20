
#ifndef PROSTREDI_H
#define PROSTREDI_H

#include "Organismus.h"
#include <list>
#include <stdlib.h>

class Organismus;



class Prostredi {
public:
    int vyska, sirka;
    std::list<Organismus*> organismy;

    Prostredi(int vyska, int sirka);
    ~Prostredi();

    void krok();
    template <typename T> void pridejOrganismus();
    template <typename T> void pridejOrganismus(int x, int y);
    void vypisStav();


};

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



#endif // PROSTREDI_H
