#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "organismus.h"

class Rostlina : public Organismus {
public:
    Rostlina(int pocatecniEnergie);
    void akce(std::vector<Organismus*>& populace) override;
    bool jeRostlina() const override;
};

#endif // ROSTLINA_H
