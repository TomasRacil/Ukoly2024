// advent_lod.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Lod {
private:
    int x;       // Souřadnice lodi X
    int y;       // Souřadnice lodi Y
    char smer;   // Směr lodi ('N', 'S', 'E', 'W')
    int wx;      // Waypoint X
    int wy;      // Waypoint Y

public:
    // Konstruktor
    Lod(int xStart, int yStart, char pocatecniSmer, int wxStart, int wyStart) {
        x = xStart;
        y = yStart;
        smer = pocatecniSmer;
        wx = wxStart;
        wy = wyStart;
    }

    // Metoda naviguj
    int naviguj(const string& nazevSouboru, bool pouzitWaypoint) {
        ifstream soubor(nazevSouboru);
        string instrukce;
        vector<string> instrukceSeznam;

        while (getline(soubor, instrukce)) {
            instrukceSeznam.push_back(instrukce);
        }

        if (!pouzitWaypoint) {
            int uhel = 0; // 0 stupňů = východ

            for (const string& instr : instrukceSeznam) {
                char akce = instr[0];
                int hodnota = stoi(instr.substr(1));

                if (akce == 'N') y += hodnota;
                else if (akce == 'S') y -= hodnota;
                else if (akce == 'E') x += hodnota;
                else if (akce == 'W') x -= hodnota;

                else if (akce == 'L') {
                    uhel = (uhel - hodnota + 360) % 360;
                }
                else if (akce == 'R') {
                    uhel = (uhel + hodnota) % 360;
                }
                else if (akce == 'F') {
                    if (uhel == 0) x += hodnota;
                    else if (uhel == 90) y -= hodnota;
                    else if (uhel == 180) x -= hodnota;
                    else if (uhel == 270) y += hodnota;
                    else {
                        // Pro úhly, které nejsou násobkem 90°
                        double rad = uhel * M_PI / 180.0;
                        x += round(cos(rad) * hodnota);
                        y -= round(sin(rad) * hodnota);
                    }
                }
            }
        }
        else {
            for (const string& instr : instrukceSeznam) {
                char akce = instr[0];
                int hodnota = stoi(instr.substr(1));

                if (akce == 'N') wy += hodnota;
                else if (akce == 'S') wy -= hodnota;
                else if (akce == 'E') wx += hodnota;
                else if (akce == 'W') wx -= hodnota;

                else if (akce == 'L' || akce == 'R') {
                    int uhel = hodnota;
                    if (akce == 'R') uhel = -hodnota;
                    uhel = (uhel + 360) % 360;

                    int puvodniWx = wx;
                    int puvodniWy = wy;

                    if (uhel == 90) {
                        wx = -puvodniWy;
                        wy = puvodniWx;
                    } else if (uhel == 180) {
                        wx = -puvodniWx;
                        wy = -puvodniWy;
                    } else if (uhel == 270) {
                        wx = puvodniWy;
                        wy = -puvodniWx;
                    }
                }

                else if (akce == 'F') {
                    x += wx * hodnota;
                    y += wy * hodnota;
                }
            }
        }

        return abs(x) + abs(y);
    }
};
