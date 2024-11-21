#ifndef MASOZRAVEC_H
#define MASOZRAVEC_H

#include "organismus.h"

class Masozravec : public Organismus {
public:
    Masozravec(int x, int y, Prostredi *prostredi);

    char getTyp() const override;
    void krok() override;
};

#endif // MASOZRAVEC_H
