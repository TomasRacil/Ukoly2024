#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <vector>
#include "zivocich.h"
#include "rostlina.h"

class Prostredi {
    int width, height;
    std::vector<Zivocich> zivocichove;
    std::vector<Rostlina> rostliny;
public:
    Prostredi(int w, int h);
    void pridejZivocicha(const Zivocich &z);
    void pridejRostlinu(const Rostlina &r);
    void simuluj(int kroky);
    void rozmnozovani();
    void zobrazStav();
    void zobrazEnergie();
};

#endif // PROSTREDI_H
