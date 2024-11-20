#include "prostredi.h"
#include "zivocich.h"
#include "rostlina.h"

int main() {
    Prostredi p(10, 10);
    
    p.pridejZivocicha(Zivocich(1, 1, 20));
    p.pridejZivocicha(Zivocich(2, 2, 20));
    p.pridejZivocicha(Zivocich(4, 5, 20));
    p.pridejZivocicha(Zivocich(7, 8, 20));
    p.pridejRostlinu(Rostlina(1, 1));
    p.pridejRostlinu(Rostlina(3, 3));
    p.pridejRostlinu(Rostlina(5, 5));
    p.pridejRostlinu(Rostlina(7, 7));
    p.pridejRostlinu(Rostlina(9, 9));
    p.simuluj(10);

    return 0;
}
