#include "organismus.h"

Organismy::Organismy(int p_x, int p_y, int p_energie) : x(p_x), y(p_y), energie(p_energie) {}

int Organismy::getX() const {
    return x;
}

int Organismy::getY() const {
    return y;
}

int Organismy::getEnergie() const {
    return energie;
}

std::string Organismy::getType() const {
    return type;
}

void Organismy::setEnergie(int en) {
    energie = en;
}
