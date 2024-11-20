#ifndef ZIVOCICH_H
#define ZIVOCICH_H

#include "organismus.h"
#include "rostlina.h"

class Zivocich : public Organismy {
public:
    Zivocich(int p_x, int p_y, int p_energie);
    void pohyb() override;
    void konzumace(Rostlina &r);
};

#endif // ZIVOCICH_H
