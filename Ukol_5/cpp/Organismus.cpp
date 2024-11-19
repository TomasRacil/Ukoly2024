#include "organismus.h"

Organismus::Organismus(int x, int y, Prostredi* prostredi)
    : x(x), y(y), prostredi(prostredi) {}

bool Organismus::jeZivy() { return energie > 0; }