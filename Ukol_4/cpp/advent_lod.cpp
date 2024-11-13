#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct Instrukce {
    char akce;
    int hodnota;
};

class Lod {
private:
    int x, y;
    char smer;
    int cilovy_bod_x, cilovy_bod_y;

    bool nactiInstrukci(ifstream& file, Instrukce& instr) {
        string line;
        if (getline(file, line)) {
            instr.akce = line[0];
            instr.hodnota = stoi(line.substr(1));
            return true;
        }
        return false;
    }

    void otocWaypoint(int& wx, int& wy, int uhel) {
        int tempX, tempY;
        switch (uhel) {
        case 90:
            tempX = wx;
            wx = wy;
            wy = -tempX;
            break;
        case 180:
            wx = -wx;
            wy = -wy;
            break;
        case 270:
            tempX = wx;
            wx = -wy;
            wy = tempX;
            break;
        }
    }

    void navigujBezWaypointu(ifstream& file) {
        int smer = 0; 
        Instrukce instr;
        while (nactiInstrukci(file, instr)) {
            switch (instr.akce) {
            case 'N': y += instr.hodnota; break;
            case 'S': y -= instr.hodnota; break;
            case 'E': x += instr.hodnota; break;
            case 'W': x -= instr.hodnota; break;
            case 'L': smer = (smer + instr.hodnota) % 360; break;
            case 'R': smer = (smer - instr.hodnota + 360) % 360; break;
            case 'F':
                switch (smer) {
                case 0: x += instr.hodnota; break;
                case 90: y += instr.hodnota; break;
                case 180: x -= instr.hodnota; break;
                case 270: y -= instr.hodnota; break;
                }
                break;
            }
        }
    }

    void navigujSWaypointem(ifstream& file) {
        int wx = cilovy_bod_x, wy = cilovy_bod_y; 
        Instrukce instr;
        while (nactiInstrukci(file, instr)) {
            switch (instr.akce) {
            case 'N': wy += instr.hodnota; break;
            case 'S': wy -= instr.hodnota; break;
            case 'E': wx += instr.hodnota; break;
            case 'W': wx -= instr.hodnota; break;
            case 'L': otocWaypoint(wx, wy, (360 - instr.hodnota) % 360); break;
            case 'R': otocWaypoint(wx, wy, instr.hodnota); break;
            case 'F':
                x += wx * instr.hodnota;
                y += wy * instr.hodnota;
                break;
            }
        }
    }

public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
        : x(x), y(y), smer(smer), cilovy_bod_x(cilovy_bod_x), cilovy_bod_y(cilovy_bod_y) {}

    int naviguj(const string& cesta_soubor, bool druhe_reseni) {
        ifstream file(cesta_soubor);
        if (!file.is_open()) {
            cerr << "Nepodarilo se otevrit soubor: " << cesta_soubor << endl;
            return -1;
        }

        if (druhe_reseni) {
            navigujSWaypointem(file);
        }
        else {
            navigujBezWaypointu(file);
        }

        file.close();
        return abs(x) + abs(y);
    }
};

#ifndef __TEST__
int main() {
    Lod lod(0, 0, 'E', 10, 1);
    cout << "Manhattanska vzdalenost bez waypointu: " << lod.naviguj("vstup_1.txt", false) << endl;
    Lod lod2(0, 0, 'E', 10, 1);
    cout << "Manhattanska vzdalenost s waypointem: " << lod2.naviguj("vstup_1.txt", true) << endl;
    return 0;
}
#endif // __TEST__
