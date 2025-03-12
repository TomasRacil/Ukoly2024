#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "organismus.h"

class Rostlina : public Organismus {
public:
    using Organismus::Organismus; // Dědí konstruktor z Organismus
    void pohyb() override {}
    void metabolismus() override;
    void rozmnozovani() override;
    void konzumuj(Organismus*) override {}
    char getTyp() const override { return 'R'; }
};

#endif // ROSTLINA_H
