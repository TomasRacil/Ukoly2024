#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

class Lod
{
private:
    int x, y;            // Souřadnice lodi
    int uhel;            // Směr lodi ve stupních (0 = východ, 90 = jih, 180 = západ, 270 = sever)
    int wx, wy;          // Waypoint souřadnice (relativní k lodi)

public:
    Lod(int x_start, int y_start, char smer, int wx_start, int wy_start)
        : x(x_start), y(y_start), wx(wx_start), wy(wy_start)
    {
        // Nastavení úhlu podle počátečního směru
        switch (smer) {
            case 'N': uhel = 270; break;
            case 'E': uhel = 0; break;
            case 'S': uhel = 90; break;
            case 'W': uhel = 180; break;
            default: uhel = 0;
        }
    }

    int naviguj(const std::string& cesta_soubor, bool druhe_reseni)
    {
        std::ifstream soubor(cesta_soubor);
        if (!soubor.is_open()) {
            std::cerr << "Nepodařilo se otevřít soubor: " << cesta_soubor << std::endl;
            return -1;
        }

        std::string instrukce;
        while (getline(soubor, instrukce)) {
            char akce = instrukce[0];
            int hodnota = std::stoi(instrukce.substr(1));

            if (druhe_reseni) {
                // Řešení s waypointem
                switch (akce) {
                    case 'N': wy += hodnota; break;
                    case 'S': wy -= hodnota; break;
                    case 'E': wx += hodnota; break;
                    case 'W': wx -= hodnota; break;
                    case 'L':
                    case 'R': {
                        int rotace = (akce == 'L') ? hodnota : 360 - hodnota;
                        rotace = (rotace + 360) % 360;
                        int puvodni_wx = wx, puvodni_wy = wy;
                        if (rotace == 90) {
                            wx = -puvodni_wy;
                            wy = puvodni_wx;
                        } else if (rotace == 180) {
                            wx = -puvodni_wx;
                            wy = -puvodni_wy;
                        } else if (rotace == 270) {
                            wx = puvodni_wy;
                            wy = -puvodni_wx;
                        }
                        break;
                    }
                    case 'F': {
                        x += wx * hodnota;
                        y += wy * hodnota;
                        break;
                    }
                }
            } else {
                // Řešení bez waypointu
                switch (akce) {
                    case 'N': y += hodnota; break;
                    case 'S': y -= hodnota; break;
                    case 'E': x += hodnota; break;
                    case 'W': x -= hodnota; break;
                    case 'L': uhel = (uhel - hodnota + 360) % 360; break;
                    case 'R': uhel = (uhel + hodnota) % 360; break;
                    case 'F':
                        if (uhel == 0) x += hodnota;
                        else if (uhel == 90) y -= hodnota;
                        else if (uhel == 180) x -= hodnota;
                        else if (uhel == 270) y += hodnota;
                        break;
                }
            }
        }

        return std::abs(x) + std::abs(y); // Výpočet Manhattan vzdálenosti
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
