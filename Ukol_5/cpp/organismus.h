#ifndef ORGANISMUS_H
#define ORGANISMUS_H

class Prostredi; // Forward deklarace

class Organismus {
public:
    int x, y; // Souřadnice
    int energie; // Energie organismu
    Prostredi* prostredi; // Ukazatel na prostředí

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
