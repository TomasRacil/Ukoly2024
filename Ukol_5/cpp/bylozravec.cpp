#include "bylozravec.h"

Bylozravec::Bylozravec(int x, int y, Prostredi *prostredi)
        : Organismus(x, y, prostredi) {}

char Bylozravec::getTyp() const {
    return 'B';
}

void Bylozravec::krok() {
    // Logika pohybu nebo chování býložravce
}
