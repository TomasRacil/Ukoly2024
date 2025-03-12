#ifndef ORGANISMUS_H
#define ORGANISMUS_H

class Prostredi; 

class Organismus {
public:
    int x, y; 
    int energie; 
    Prostredi* prostredi; 

int getX() const { return x; }
    int getY() const { return y; }

    Organismus(int x, int y, Prostredi* prostredi);
    virtual ~Organismus() = default;

    virtual void pohyb() = 0;
    virtual void metabolismus() = 0;
    virtual void rozmnozovani() = 0;
    virtual bool jeZivy() const;
    virtual void konzumuj(Organismus* other) = 0;
    virtual char getTyp() const = 0;
};

#endif // ORGANISMUS_H
