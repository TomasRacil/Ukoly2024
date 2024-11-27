//
// Created by Jakub Václav Flasar on 18.11.2024.
//
#include "organismus.h"

Organismus::Organismus(int x, int y, Prostredi *prostredi)
    : x(x), y(y), prostredi(prostredi) {}

bool Organismus::jeZivy() { return energie > 0; }
