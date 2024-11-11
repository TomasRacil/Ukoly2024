#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
class Lod
{
private:
    int x;
    int y;
    char stupne;
    int waypoint_x;
    int waypoint_y;
    
    void rotaceWaypointu(int uhel) {
        int nove_x, nove_y;
        uhel = (uhel + 360) % 360; // normalizace uhlu
        switch (uhel) {
            case 90:
                nove_x = waypoint_y;
                nove_y = -waypoint_x;
                break;
            case 180:
                nove_x = -waypoint_x;
                nove_y = -waypoint_y;
                break;
            case 270:
                nove_x = -waypoint_y;
                nove_y = waypoint_x;
                break;
            default:
                return;
        }
        waypoint_x = nove_x;
        waypoint_y = nove_y;
    }

    void pohyb(char smer, int hodnota, bool druhe_reseni) {
        // pokud bude druhe reseni true, nastavi se cil na souradnice waypointu
        // pokud bude druhe reseni false, nastavi se cil na souradnice lodi
        int* cil_x = druhe_reseni ? &waypoint_x : &x;
        int* cil_y = druhe_reseni ? &waypoint_y : &y;

        switch (smer) {
            case 'N': *cil_y += hodnota; break;
            case 'S': *cil_y -= hodnota; break;
            case 'E': *cil_x += hodnota; break;
            case 'W': *cil_x -= hodnota; break;
        }
    }

    // Pohyb lodi směrem k waypointu
    void pohybVPred(int hodnota) {
        x += waypoint_x * hodnota;
        y += waypoint_y * hodnota;
    }

    // Otočení směru lodi (pro část 1)
    void otoceniLodi(int uhel) {
        stupne = (stupne + uhel + 360) % 360;
    }

    // Výpočet aktuálního směru podle stupňů (pro část 1)
    char aktualniSmer() const {
        switch (stupne) {
            case 0: return 'E';
            case 90: return 'S';
            case 180: return 'W';
            case 270: return 'N';
            default: return 'E';
        }
    }

public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    : x(x), y(y), waypoint_x(cilovy_bod_x), waypoint_y(cilovy_bod_y)
    {
        switch (smer) {
            case 'N': stupne = 270; break;
            case 'S': stupne = 90; break;
            case 'E': stupne = 0; break;
            case 'W': stupne = 180; break;
        }
    }

    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
        ifstream soubor(cesta_soubor); // vytvoreni objektu soubor
        string instrukce;

        if (!soubor.is_open()) {
            cerr << "Chyba pri otevirani souboru" << endl;
            return 0;
        }

        while (getline(soubor, instrukce)) {
            char akce = instrukce[0]; // nulty znak na kazdem radku je char s akci
            int hodnota = stoi(instrukce.substr(1)); // na kazdem radku precte znaky od indexu 1 do konce a udela z nich int hodnota

            if (akce == 'L' || akce == 'R') {
                int uhel = (akce == 'L' ? -hodnota : hodnota); // pokud je akce L, pak se hodnota da do zaporu (budeme otacet na druhou stranu, jinak nastav hodnota)
                if (druhe_reseni) {
                    rotaceWaypointu(uhel);
                } else {
                    otoceniLodi(uhel);
                }
            } else if (akce == 'F') {
                if (druhe_reseni) {
                    pohybVPred(hodnota);
                } else {
                    pohyb(aktualniSmer(), hodnota, false);
                }
            } else {
                pohyb(akce, hodnota, druhe_reseni);
            }
        }
        soubor.close();
        return abs(x) + abs(y);
    }
};

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