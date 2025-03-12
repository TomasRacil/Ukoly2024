#include "Rostlina.h"
#include "Bylozravec.h"
#include "Masozravec.h"
#include "Prostredi.h"


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