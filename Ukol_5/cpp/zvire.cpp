//
// Created by Jakub Václav Flasar on 18.11.2024.
//

#include <random>
#include "zvire.h"
#include "prostredi.h"

// Definice metod Zvire mimo tělo třídy
void Zvire::pohyb()
{
    x = std::max(0, std::min(prostredi->sirka - 1, x + rand() % 3 - 1));
    y = std::max(0, std::min(prostredi->vyska - 1, y + rand() % 3 - 1));
}

void Zvire::metabolismus() {
    energie -= 2;
}
