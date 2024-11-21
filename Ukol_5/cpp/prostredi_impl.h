#ifndef PROSTREDI_IMPL_H
#define PROSTREDI_IMPL_H

#include <algorithm>
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"

template<typename T>
void Prostredi::pridejOrganismus() {
    T *organismus = new T(rand() % sirka, rand() % vyska, this);
    organismy.push_back(organismus);
}

template<typename T>
void Prostredi::pridejOrganismus(int x, int y) {
    int new_position_x = std::max(0, std::min(sirka - 1, x));
    int new_position_y = std::max(0, std::min(vyska - 1, y));

    T *organismus = new T(new_position_x, new_position_y, this);
    organismy.push_back(organismus);
}

#endif
