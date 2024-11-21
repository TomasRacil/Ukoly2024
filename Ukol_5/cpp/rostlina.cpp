#include "rostlina.h"

Rostlina::Rostlina(int x, int y, Prostredi *prostredi)
        : Organismus(x, y, prostredi) {}

char Rostlina::getTyp() const {
    return 'R';
}

void Rostlina::krok() {
    // Rostlina se nehýbe, ale může mít vlastní logiku, třeba růst
}
