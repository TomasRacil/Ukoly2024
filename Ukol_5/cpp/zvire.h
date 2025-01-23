#ifndef ZVIRE_H
#define ZVIRE_H

#include "organismus.h"

class Zvire : public Organismus {
public:
    Zvire(int pocatecniEnergie);
    void akce(std::vector<Organismus*>& populace) override;
    bool jeRostlina() const override;
};

#endif // ZVIRE_H