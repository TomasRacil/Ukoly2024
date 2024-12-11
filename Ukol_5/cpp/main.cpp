// main.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"
#include "prostredi.h"


int main()
{
    Prostredi prostredi(20, 20);

    prostredi.pridejOrganismus<Rostlina>();
    prostredi.pridejOrganismus<Rostlina>();
    prostredi.pridejOrganismus<Rostlina>();
    prostredi.pridejOrganismus<Rostlina>();
    prostredi.pridejOrganismus<Rostlina>();
    prostredi.pridejOrganismus<Rostlina>();
    prostredi.pridejOrganismus<Rostlina>();
    prostredi.pridejOrganismus<Rostlina>();

    prostredi.pridejOrganismus<Bylozravec>();
    prostredi.pridejOrganismus<Bylozravec>();
    prostredi.pridejOrganismus<Bylozravec>();
    prostredi.pridejOrganismus<Bylozravec>();

    prostredi.pridejOrganismus<Masozravec>();
    prostredi.pridejOrganismus<Masozravec>();

    prostredi.vypisStav();

    for (int i = 0; i < 40; ++i)
    {
        prostredi.krok();
        prostredi.vypisStav();
    }

    return 0;
}