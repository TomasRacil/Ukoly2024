#include "prostredi.h"
#include <iostream>

int main() {
    Prostredi svet(20, 20);

    svet.pridatOrganismus(new Rostlina(5, 5));
    svet.pridatOrganismus(new Zivocich(10, 10));
    svet.pridatOrganismus(new Zivocich(15, 15));

    svet.simuluj(10);

    return 0;
}
