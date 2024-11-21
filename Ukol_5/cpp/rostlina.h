#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "organismus.h"

class Rostlina : public Organismus {
public:
    Rostlina(int x, int y, Prostredi *prostredi);

    char getTyp() const override;
    void krok() override;
};

#endif // ROSTLINA_H
