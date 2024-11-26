#include "prostredi.h"
#include "rostlina.h"
#include "zvire.h"

int main() {
    Prostredi ekosystem;

    ekosystem.pridatOrganismus(new Rostlina(30));
    ekosystem.pridatOrganismus(new Zvire(60));
    ekosystem.pridatOrganismus(new Rostlina(40));
    ekosystem.pridatOrganismus(new Zvire(80));

    ekosystem.simulace(10);

    return 0;
}
