#ifndef prostredi_h
#define prostredi_h
#include <list>
#include <random>
#include "organismus.h"
using namespace std;
class Prostredi
{
public:
    int vyska,sirka;
    std::list<Organismus *> organismy;
    Prostredi(int vyska, int sirka);

    void krok();
    template <typename T>
    void pridejOrganismus()
    {
        T *organismus = new T(rand() % sirka, rand() % vyska, this);
        organismy.push_back(organismus);
    }
    template <typename T>
    void pridejOrganismus(int x, int y)
    {
        int new_position_x = std::max(0, std::min(sirka - 1, x + rand() % 3 - 1));
        int new_position_y = std::max(0, std::min(vyska - 1, y + rand() % 3 - 1));

        T *organismus = new T(new_position_x, new_position_y, this);
        organismy.push_back(organismus);
    }
    void odeberOrganismus(Organismus *o);
    void vypisStav();









};

#endif // prostredi_h