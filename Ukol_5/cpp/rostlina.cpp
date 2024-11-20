//
// Created by danda on 18.11.2024.
//

#include "bylozravec.h"
#include "zvire.h"
#include "organismus.h"
#include <random>
#include <list>
#include <vector>
#include <iostream>
#include "rostlina.h"

void Rostlina::rozmnozovani()
{
    if (energie > 30)
    {
        int pocetPotomku = rand() % 10;

        for (int i = 0; i < pocetPotomku; ++i)
        {
            prostredi->pridejOrganismus<Rostlina>();
            energie /= 2;
        }
    }
}