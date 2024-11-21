#include "organismus.h"

Organismus::Organismus(int x, int y, Prostredi *prostredi)
        : x(x), y(y), prostredi(prostredi), zivy(true) {}

bool Organismus::jeZivy() const {
    return zivy;
}
