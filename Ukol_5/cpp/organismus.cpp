#include "organismus.h"
#include "prostredi.h"

Organismus::Organismus(int x, int y, Prostredi *prostredi)
        : x(x), y(y), prostredi(prostredi), energie(0) {}

bool Organismus::jeZivy() {
    return energie > 0;
}
