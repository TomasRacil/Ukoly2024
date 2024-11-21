#ifndef ORGANISMUS_H
#define ORGANISMUS_H

class Prostredi; // Forward deklarace

class Organismus {
protected:
    int x, y;
    Prostredi *prostredi;
    bool zivy;

public:
    Organismus(int x, int y, Prostredi *prostredi);
    virtual ~Organismus() = default;

    virtual char getTyp() const = 0; // Čistě virtuální metoda
    virtual void krok() = 0;         // Čistě virtuální metoda krok()

    bool jeZivy() const;
};

#endif // ORGANISMUS_H
