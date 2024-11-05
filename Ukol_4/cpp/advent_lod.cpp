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
        // Nastavíme úhel podle počátečního směru
        switch (pocatecni_smer) {
            case 'N': uhel = 270; break;
            case 'E': uhel = 0; break;
            case 'S': uhel = 90; break;
            case 'W': uhel = 180; break;
        }
    }

    // Navigační funkce
    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
        std::ifstream soubor(cesta_soubor);
        if (!soubor.is_open())
        {
            std::cerr << "Nepodařilo se otevřít soubor: " << cesta_soubor << std::endl;
            return -1;
        }

        std::string instrukce;
        while (getline(soubor, instrukce))
        {
            char akce = instrukce[0];
            int hodnota = std::stoi(instrukce.substr(1));

            if (druhe_reseni)
            {
                // Řešení s waypointem
                if (akce == 'N')
                    wy += hodnota;
                else if (akce == 'S')
                    wy -= hodnota;
                else if (akce == 'E')
                    wx += hodnota;
                else if (akce == 'W')
                    wx -= hodnota;
                else if (akce == 'L' || akce == 'R')
                {
                    int uhel = (akce == 'L') ? hodnota : 360 - hodnota;
                    uhel = (uhel + 360) % 360;

                    // Rotace waypointu kolem lodi
                    int puvodni_wx = wx, puvodni_wy = wy;
                    if (uhel == 90)
                    {
                        wx = -puvodni_wy;
                        wy = puvodni_wx;
                    }
                    else if (uhel == 180)
                    {
                        wx = -puvodni_wx;
                        wy = -puvodni_wy;
                    }
                    else if (uhel == 270)
                    {
                        wx = puvodni_wy;
                        wy = -puvodni_wx;
                    }
                }
                else if (akce == 'F')
                {
                    x += wx * hodnota;
                    y += wy * hodnota;
                }
            }
            else
            {
                // Řešení bez waypointu (přímý pohyb lodi)
                if (akce == 'N')
                    y += hodnota;
                else if (akce == 'S')
                    y -= hodnota;
                else if (akce == 'E')
                    x += hodnota;
                else if (akce == 'W')
                    x -= hodnota;

                // Otočení lodi změnou úhlu (vpravo nebo vlevo)
                else if (akce == 'L')
                    uhel = (uhel - hodnota + 360) % 360;
                else if (akce == 'R')
                    uhel = (uhel + hodnota) % 360;

                // Pohyb lodi vpřed podle aktuálního úhlu
                else if (akce == 'F') {
                    if (uhel == 0) x += hodnota;        // Východ
                    else if (uhel == 90) y -= hodnota;  // Jih
                    else if (uhel == 180) x -= hodnota; // Západ
                    else if (uhel == 270) y += hodnota; // Sever
                }
            }
        }

        return std::abs(x) + std::abs(y); // Manhattan vzdálenost
    }
};

#ifndef __TEST__
int main()
{
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << "Manhattan vzdálenost (bez waypointu): " << lod.naviguj("/workspaces/Ukoly2024/Ukoly2024/Ukol_4/cpp/advent_lod/vstup_1.txt", false) << std::endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << "Manhattan vzdálenost (s waypointem): " << lod2.naviguj("/workspaces/Ukoly2024/Ukoly2024/Ukol_4/cpp/advent_lod/vstup_1.txt", true) << std::endl;
    return 0;
}
#endif // __TEST__

