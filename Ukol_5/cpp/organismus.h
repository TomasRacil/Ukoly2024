#ifndef ORGANISMUS_H
#define ORGANISMUS_H
#include "prostredi.h"
using namespace std;
class Organismus
{
    public:
    Organismus(int x, int y, Prostredi *prostredi);
    char getType() const;
    void pohyb();
    void metabolismus();
    void rozmnozovani();
    bool JeZivy();
    void konzumuj(Organismus *other);


  
    int x,y;
    int energie;
    Prostredi *prostredi;
};






#endif