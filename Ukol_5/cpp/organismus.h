#ifndef ORGANISMUS_H
#define ORGANISMUS_H

class Prostredi; // Forward declaration

class Organismus {
protected:
    int x, y;               // Souřadnice organismu
    Prostredi *prostredi;   // Ukazatel na prostředí, kde se organismus nachází
    bool zivy;              // Indikátor, zda je organismus živý

public:
    Organismus(int x, int y, Prostredi *prostredi);
    virtual ~Organismus() = default;

    virtual void krok() = 0; // Virtuální metoda pro akce organismu v jednom kroku
    bool jeZivy() const;     // Kontrola, zda je organismus živý
};

#endif // ORGANISMUS_H
