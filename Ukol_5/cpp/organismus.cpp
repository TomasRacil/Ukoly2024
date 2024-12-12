//includes in .cpp file to avoid cyclic reference
#include "organismus.hpp"
#include "prostredi.hpp"

Organismus::Organismus(int x, int y, Prostredi *prostredi) : x(x), y(y), prostredi(prostredi) {}

bool Organismus::jeZivy() {
    return energie > 0;
}