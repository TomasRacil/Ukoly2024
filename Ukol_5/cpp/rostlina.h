//
// Created by danda on 18.11.2024.
//

#ifndef HEADERS_ROSTLINA_H
#define HEADERS_ROSTLINA_H

#include "organismus.h"
#include "prostredi.h"


class Rostlina : public Organismus
{
public:
    Rostlina(int x, int y, Prostredi *prostredi) : Organismus(x, y, prostredi)
    {
        energie = 10;
    }

    void pohyb() override {}

    void metabolismus() override
    {
        energie += 1;
    }

    void rozmnozovani() override;

    void konzumuj(Organismus *other) override {}
    char getTyp() override { return 'R'; }
};

#endif //HEADERS_ROSTLINA_H
