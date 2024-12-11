#ifndef ORGANISMUS_H
#define ORGANISMUS_H
using namespace std;


// Forward deklarace třídy Prostredi, protože ji potřebujeme v definici Organismus,
// ale nechceme zatím zahrnout celý její obsah (zabraňuje cyklickým závislostem).
class Prostredi;
class Organismus
{
public:
    Organismus(int x, int y, Prostredi *prostredi);
    virtual char getType() const = 0;
    virtual void pohyb() = 0;
    virtual void metabolismus() = 0;
    virtual void rozmnozovani() = 0;
    virtual bool JeZivy();
    virtual void konzumuj(Organismus *other) = 0;

    int x,y;
    int energie;
    Prostredi *prostredi;
};

#endif