#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "organismus.hpp"

#include <random>

class Rostlina : public Organismus {
public:
    Rostlina(int x, int y, Prostredi *prostredi);
    ~Rostlina() {};

    void metabolismus() override;
    void rozmnozovani() override;
    void konzumuj(Organismus *other) override;
    void pohyb() override {};
    char getTyp() override;
};
#endif