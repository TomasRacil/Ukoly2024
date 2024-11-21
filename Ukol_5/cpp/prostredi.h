#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <list>
#include "organismus.h"
//kebab
class Prostredi {
private:
    int vyska, sirka;
    std::list<Organismus *> organismy;

public:
    Prostredi(int vyska, int sirka);
    ~Prostredi();

    void vypisStav();
    void krok();

    template <typename T>
    void pridejOrganismus();
};

#endif // PROSTREDI_H
