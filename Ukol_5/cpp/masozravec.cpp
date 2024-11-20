//
// Created by danda on 18.11.2024.
//

#include "rostlina.h"
#include "bylozravec.h"
#include "zvire.h"
#include "organismus.h"
#include <random>
#include <list>
#include <vector>
#include <iostream>
#include "masozravec.h"

void Masozravec::rozmnozovani()
{
    if (energie > 500)
    {
        int pocetPotomku = rand() % 2;

        for (int i = 0; i < pocetPotomku; ++i)
        {
            prostredi->pridejOrganismus<Masozravec>(x, y);
            energie /= 2;
        }
    }
}