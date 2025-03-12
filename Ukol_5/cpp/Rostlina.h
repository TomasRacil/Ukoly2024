
#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "Organismus.h"

class Rostlina : public Organismus {
public:
    Rostlina(int x, int y, Prostredi* prostredi);
    void pohyb() override;
    void metabolismus() override;
    void rozmnozovani() override;
    void konzumuj(Organismus* other) override;
    char getTyp() override;
};

#endif //ROSTLINA_H
