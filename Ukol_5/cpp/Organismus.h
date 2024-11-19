#ifndef ORGANISMUS_H
#define ORGANISMUS_H

class Prostredi;

class Organismus
{
public:
    int x, y;
    int energie;
    Prostredi* prostredi;

    Organismus(int x, int y, Prostredi* prostredi);

    virtual void pohyb() = 0;
    virtual void metabolismus() = 0;
    virtual void rozmnozovani() = 0;
    virtual bool jeZivy();
    virtual void konzumuj(Organismus* other) = 0;
    virtual char getTyp() = 0; 
};


#endif 