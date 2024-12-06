#ifndef PROSTREDI_H
#define PROSTREDI_H

#include "organismus.h"
#include <vector>

class Prostredi {
public:
    Prostredi();
    ~Prostredi();
    void pridatOrganismus(Organismus* organismus);
    void simulace(int kola);

private:
    std::vector<Organismus*> populace;
    void odstranMrtve();
};

#endif // PROSTREDI_H
