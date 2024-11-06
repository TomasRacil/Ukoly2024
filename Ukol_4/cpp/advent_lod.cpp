#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

class Lod
{
private:
    int x;       // Aktuální souřadnice lodi X
    int y;       // Aktuální souřadnice lodi Y
    int uhel;    // Směr lodi ve stupních (0 = východ, 90 = jih, 180 = západ, 270 = sever)
    int wx;      // Waypoint X souřadnice (relativní k lodi)
    int wy;      // Waypoint Y souřadnice (relativní k lodi)

public:
    // Konstruktor
    Lod(int x_start, int y_start, char pocatecni_smer, int wx_start, int wy_start)
        : x(x_start), y(y_start), wx(wx_start), wy(wy_start)
    {
        switch (pocatecni_smer) {
            case 'N': uhel = 270; break;
            case 'E': uhel = 0; break;
            case 'S': uhel = 90; break;
            case 'W': uhel = 180; break;
        }
    }

    // Navigační funkce s kontrolou různých cest
    int naviguj(const std::string& cesta_soubor, bool druhe_reseni)
    {
        std::ifstream soubor;

        // Pokus o otevření souboru v aktuálním adresáři
        soubor.open(cesta_soubor);
        if (!soubor.is_open()) {
            // Pokud soubor není otevřen, zkusí otevřít s relativní cestou
            soubor.open("advent_lod/" + cesta_soubor);
        }

        // Pokud se soubor stále nepodařilo otevřít, vypíše chybu
        if (!soubor.is_open()) {
            std::cerr << "Nepodařilo se otevřít soubor: " << cesta_soubor << std::endl;
            return -1;
        }

        std::string instrukce;
        while (getline(soubor, instrukce))
        {
            if (instrukce.empty()) continue;

            char akce = instrukce[0];
            int hodnota;

            try {
                hodnota = std::stoi(instrukce.substr(1));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Neplatná instrukce: " << instrukce << std::endl;
                continue;
            }

            if (druhe_reseni)
            {
                // Řešení s waypointem
                if (akce == 'N') wy += hodnota;
                else if (akce == 'S') wy -= hodnota;
                else if (akce == 'E') wx += hodnota;
                else if (akce == 'W') wx -= hodnota;
                else if (akce == 'L' || akce == 'R')
                {
                    int uhel = (akce == 'L') ? hodnota : 360 - hodnota;
                    uhel = (uhel + 360) % 360;

                    int puvodni_wx = wx, puvodni_wy = wy;
                    if (uhel == 90) { wx = -puvodni_wy; wy = puvodni_wx; }
                    else if (uhel == 180) { wx = -puvodni_wx; wy = -puvodni_wy; }
                    else if (uhel == 270) { wx = puvodni_wy; wy = -puvodni_wx; }
                }
                else if (akce == 'F') {
                    x += wx * hodnota;
                    y += wy * hodnota;
                }
            }
            else
            {
                if (akce == 'N') y += hodnota;
                else if (akce == 'S') y -= hodnota;
                else if (akce == 'E') x += hodnota;
                else if (akce == 'W') x -= hodnota;
                else if (akce == 'L') uhel = (uhel - hodnota + 360) % 360;
                else if (akce == 'R') uhel = (uhel + hodnota) % 360;
                else if (akce == 'F') {
                    if (uhel == 0) x += hodnota;
                    else if (uhel == 90) y -= hodnota;
                    else if (uhel == 180) x -= hodnota;
                    else if (uhel == 270) y += hodnota;
                }
            }
        }

        return std::abs(x) + std::abs(y);
    }
};

#ifndef __TEST__
int main()
{
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << "Manhattan vzdálenost (bez waypointu): " << lod.naviguj("vstup_1.txt", false) << std::endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << "Manhattan vzdálenost (s waypointem): " << lod2.naviguj("vstup_1.txt", true) << std::endl;
    return 0;
}
#endif // __TEST__
