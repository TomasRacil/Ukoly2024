#include "masozravec.h"

Masozravec::Masozravec(int x, int y, Prostredi *prostredi)
        : Organismus(x, y, prostredi) {}

char Masozravec::getTyp() const {
    return 'M';
}

void Masozravec::krok() {
    // Logika pohybu nebo chování masožravce
}
