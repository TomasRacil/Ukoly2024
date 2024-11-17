#include <iostream>

#include "prostredi.hpp"
#include "masozravec.hpp"
#include "bylozravec.hpp"
#include "rostlina.hpp"

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
       prostredi.krok(), prostredi.vypisStav();
    }

    //destructor of the prostredi class deletes all members
    return 0;
}