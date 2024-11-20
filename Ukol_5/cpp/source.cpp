#include "prostredi.h"
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"
#include "prostredi.cpp"
#include "masozravec.cpp"
#include "bylozravec.cpp"
#include "rostlina.cpp"
#include "zvire.cpp"
#include "organismus.cpp"

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

    for (int i = 0; i < 50; ++i)
    {
        prostredi.krok();
        prostredi.vypisStav();
    }

    return 0;
}