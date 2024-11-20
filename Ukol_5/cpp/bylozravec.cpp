//
// Created by danda on 18.11.2024.
//

#include "zvire.h"
#include "organismus.h"
#include <random>
#include <list>
#include <vector>
#include <iostream>
#include "bylozravec.h"

void Bylozravec::rozmnozovani()
{
    if (energie > 300)
    {
        int pocetPotomku = rand() % 4;

        for (int i = 0; i < pocetPotomku; ++i)
        {
            prostredi->pridejOrganismus<Bylozravec>(x, y);
            energie /= 2;
        }
    }
}