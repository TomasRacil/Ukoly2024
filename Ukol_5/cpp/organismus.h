//
// Created by danda on 18.11.2024.
//

#ifndef HEADERS_ORGANISMUS_H
#define HEADERS_ORGANISMUS_H

#include "prostredi.h"
class Prostredi;

class Organismus
{
public:
    int x, y;
    int energie;
    Prostredi *prostredi;

    Organismus(int x, int y, Prostredi *prostredi) : x(x), y(y), prostredi(prostredi) {}

    virtual void pohyb() = 0;
    virtual void metabolismus() = 0;
    virtual void rozmnozovani() = 0;
    virtual bool jeZivy() { return energie > 0; }
    virtual void konzumuj(Organismus *other) = 0;
    virtual char getTyp() = 0; // Pro identifikaci typu organismu
};

#endif //HEADERS_ORGANISMUS_H
