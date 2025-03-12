#include "organismus.h"
#include "prostredi.h"

Organismus::Organismus(int x, int y, Prostredi* prostredi)
    : x(x), y(y), energie(0), prostredi(prostredi) {}

bool Organismus::jeZivy() const {
    return energie > 0;
}
