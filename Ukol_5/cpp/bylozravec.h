#ifndef BYLOZRAVEC_H
#define BYLOZRAVEC_H

#include "organismus.h"

class Bylozravec : public Organismus {
public:
    Bylozravec(int x, int y, Prostredi *prostredi);

    char getTyp() const override;
    void krok() override;
};

#endif // BYLOZRAVEC_H
