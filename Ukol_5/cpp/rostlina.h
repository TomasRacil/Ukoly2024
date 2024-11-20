#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "organismus.h"

class Rostlina : public Organismy {
public:
    Rostlina(int p_x, int p_y);
    void pohyb() override;
};

#endif // ROSTLINA_H
