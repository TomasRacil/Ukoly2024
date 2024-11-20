#include "zivocich.h"
#include <cstdlib>

Zivocich::Zivocich(int p_x, int p_y, int p_energie) : Organismy(p_x, p_y, p_energie) {
    type = "zivocich";
}

void Zivocich::pohyb() {
    x += rand() % 3 - 1; 
    y += rand() % 3 - 1; 
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= 10) x = 9; 
    if (y >= 10) y = 9; 
}

void Zivocich::konzumace(Rostlina &r) {
    if (x == r.getX() && y == r.getY() && r.getEnergie() > 0) {
        energie += r.getEnergie();
        r.setEnergie(0); 
    }
}
