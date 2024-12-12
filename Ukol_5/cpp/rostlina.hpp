#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "organismus.hpp"
#include "prostredi.hpp"

#include <random>

class Rostlina : public Organismus {
public:
    Rostlina(int x, int y, Prostredi *prostredi);

    void metabolismus() override;
    void rozmnozovani() override;
    void pohyb() override {};
    char getTyp() override;
    
    //silence unused parameter warning, Rostlina class does NOT consume anything
    void konzumuj(Organismus *other) override {(void)other;};
};
#endif