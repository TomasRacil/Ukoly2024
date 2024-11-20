#ifndef ORGANISMUS_H
#define ORGANISMUS_H

class Prostredi;

class Organismus
{
public:
    Organismus(int x, int y, Prostredi* prostredi);
    virtual ~Organismus() = default;

    virtual void pohyb() = 0;
    virtual void metabolismus() = 0;
    virtual void rozmnozovani() = 0;
    virtual void konzumuj(Organismus* other) = 0;
    virtual char getTyp() = 0;
    bool jeZivy();

protected:
    int x, y;
    int energie;
    Prostredi* prostredi;
};

#endif // ORGANISMUS_H
