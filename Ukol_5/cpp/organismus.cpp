#include "organismus.h"

Organismus::Organismus(int pocatecniEnergie) : energie(pocatecniEnergie) {}

Organismus::~Organismus() {}

bool Organismus::jeMrtvy() const {
    return energie <= 0;
}

void Organismus::pridejEnergii(int hodnota) {
    energie += hodnota;
}

int Organismus::getEnergie() const {
    return energie;
}
