#include <iostream>
#include "organismus.h"  
#include "prostredi.h"

int main() {
    Prostredi prostredi(20, 20);

    prostredi.pridatOrganismus(new Rostlina(5, 5));
    prostredi.pridatOrganismus(new Bylozravec(10, 10));
    prostredi.pridatOrganismus(new Masozravec(15, 15));

    prostredi.simuluj(400);

    return 0;
}
