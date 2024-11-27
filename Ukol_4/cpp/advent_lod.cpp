#include <iostream>
#include <fstream>
#include <string>

class Lod
{
private:
public:
    int shipX, shipY, pointX, pointY, val, state;
    char way;
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y);
    int naviguj(std::string cesta_soubor, bool druhe_reseni);
    void moveShip();
    void movePoint();
};

Lod::Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y) { // konstruktor a načtení hodnot
    shipX = x; shipY = y; way = smer; pointX = cilovy_bod_x; pointY = cilovy_bod_y; state = 1; val = 0; 
}

void Lod::movePoint() {
    // | N=0 Y+ | E=1 X+| S=2 Y- | W = 3 X- |

    if (way == 'R' || way =='L') {
        int newState = (way == 'R' ? -val : val) / 90;
        for (int i = 0; i < abs(newState); i++) {
            int rem = pointX;
            pointX = newState > 0 ? -pointY : pointY;
            pointY = newState > 0 ? rem : -rem;

        }
    }
    
    switch (way) {
    case 'N':
        pointY += val;
        break;
    case 'E':
        pointX += val;
        break;
    case 'S':
        pointY -= val;
        break;
    case 'W':
        pointX -= val;
        break;
    case 'F':
        shipX += pointX * val;
        shipY += pointY * val;
        break;
    }
}

void Lod::moveShip() {
    int rem = 0;
    // | N=0 Y+ | E=1 X+| S=2 Y- | W = 3 X- |
    if (false) {
    forward:
        way = "NESW"[state];
    }
    switch (way) {
    case 'N':
        shipY += val;
        break;
    case 'E':
        shipX += val;
        break;
    case 'S':
        shipY -= val;
        break;
    case 'W':
        shipX -= val;
        break;
    case 'L':
        while (val > 0) {
            val -= 90;
            state--;
            if (state < 0) {
                state = 4 + state;
            }

        }

        break;
    case 'R':
        while (val > 0) {
            val -= 90;
            state++;
            if (state >= 4) {
                state = state - 4;
            }

        }
        break;
    case 'F':
        goto forward;
        break;
    }
}

int Lod::naviguj(std::string cesta_soubor, bool druhe_reseni) {
    std::ifstream file(cesta_soubor);
    if (!file) {
        return 0; // nelze otevřít
    }
    std::string line;
    while (getline(file, line)) {
        way = line[0];
        line[0] = '0';
        val = stoi(line);
        if (druhe_reseni) { 
            movePoint();
        }
        else {
            moveShip();
        }
    }
    return (abs(shipX) + abs(shipY));
}

#ifndef __TEST__
int main()
{
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << lod.naviguj("vstup_1.txt", false) << std::endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << lod2.naviguj("vstup_1.txt", true) << std::endl;


    return 0;
}
#endif // __TEST__
