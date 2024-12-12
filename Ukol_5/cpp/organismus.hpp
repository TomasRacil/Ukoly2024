#ifndef ORGANISMUS_H
#define ORGANISMUS_H

//forward declaration to avoid cyclic reference
class Prostredi;

class Organismus {
public:
    int x, y;
    int energie;
    Prostredi *prostredi;

    Organismus(int x, int y, Prostredi *prostredi);
    //virtual destructor is necessary because slaves will be deleted by poiner to this master class
    virtual ~Organismus() {};

    virtual void pohyb() = 0;
    virtual void metabolismus() = 0;
    virtual void rozmnozovani() = 0;
    virtual bool jeZivy();
    virtual void konzumuj(Organismus *other) = 0;
    //returns char representing first character of class name - B,M or R
    virtual char getTyp() = 0;
};

#endif