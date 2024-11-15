

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

class Lod
{
private:
    int x, y; // Souřadnice lodi
    int waypoint_x, waypoint_y; // Souřadnice waypointu relativně k lodi
    char smer; // Směr lodi ('N', 'S', 'E', 'W')

public:
    Lod(int start_x, int start_y, char start_smer, int waypoint_x_init, int waypoint_y_init)
        : x(start_x), y(start_y), smer(start_smer), waypoint_x(waypoint_x_init), waypoint_y(waypoint_y_init) {}

    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
        std::ifstream vstup(cesta_soubor);
        if (!vstup.is_open())
        {
            std::cerr << "Chyba při otevírání souboru." << std::endl;
            return -1;
        }

        std::string instrukce;
        while (std::getline(vstup, instrukce))
        {
            char akce = instrukce[0];
            int hodnota = std::stoi(instrukce.substr(1));

            if (druhe_reseni)
            {
                if (akce == 'N') waypoint_y += hodnota;
                else if (akce == 'S') waypoint_y -= hodnota;
                else if (akce == 'E') waypoint_x += hodnota;
                else if (akce == 'W') waypoint_x -= hodnota;
                else if (akce == 'L' || akce == 'R') otoc_waypoint(akce, hodnota);
                else if (akce == 'F') {
                    x += hodnota * waypoint_x;
                    y += hodnota * waypoint_y;
                }
            }
            else
            {
                if (akce == 'N') y += hodnota;
                else if (akce == 'S') y -= hodnota;
                else if (akce == 'E') x += hodnota;
                else if (akce == 'W') x -= hodnota;
                else if (akce == 'L' || akce == 'R') otoc_lod(akce, hodnota);
                else if (akce == 'F') pohyb_vpred(hodnota);
            }
        }

        vstup.close();
        return std::abs(x) + std::abs(y);
    }

private:
    void otoc_lod(char akce, int stupne)
    {
        int nasobek = (akce == 'L' ? -1 : 1);
        int nove_smerovani = ((smer_to_deg(smer) + nasobek * stupne) % 360 + 360) % 360;
        smer = deg_to_smer(nove_smerovani);
    }

    void otoc_waypoint(char akce, int stupne)
    {
        int nasobek = (akce == 'L' ? 1 : -1);
        int rotace = ((nasobek * stupne) % 360 + 360) % 360;
        int nove_x, nove_y;
        if (rotace == 90)
        {
            nove_x = -waypoint_y;
            nove_y = waypoint_x;
        }
        else if (rotace == 180)
        {
            nove_x = -waypoint_x;
            nove_y = -waypoint_y;
        }
        else if (rotace == 270)
        {
            nove_x = waypoint_y;
            nove_y = -waypoint_x;
        }
        else
        {
            return;
        }
        waypoint_x = nove_x;
        waypoint_y = nove_y;
    }

    void pohyb_vpred(int hodnota)
    {
        if (smer == 'N') y += hodnota;
        else if (smer == 'S') y -= hodnota;
        else if (smer == 'E') x += hodnota;
        else if (smer == 'W') x -= hodnota;
    }

    int smer_to_deg(char smer)
    {
        if (smer == 'E') return 0;
        if (smer == 'N') return 90;
        if (smer == 'W') return 180;
        if (smer == 'S') return 270;
        return 0;
    }

    char deg_to_smer(int stupne)
    {
        if (stupne == 0) return 'E';
        if (stupne == 90) return 'N';
        if (stupne == 180) return 'W';
        if (stupne == 270) return 'S';
        return 'E';
    }
};

#ifndef __TEST__
int main()
{
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << "Vzdálenost bez waypointu: " << lod.naviguj("vstup_1.txt", false) << std::endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << "Vzdálenost s waypointem: " << lod2.naviguj("vstup_1.txt", true) << std::endl;
    return 0;
}
#endif // __TEST__






/*
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

class Lod 
{
private:
    int x, y; // Aktuální pozice lodi
    int waypoint_x, waypoint_y; // Relativní pozice waypointu
    char smer; // Směr lodi ('N', 'E', 'S', 'W')

public:
    Lod(int start_x, int start_y, char start_smer, int waypoint_x_init, int waypoint_y_init)
        : x(start_x), y(start_y), smer(start_smer), waypoint_x(waypoint_x_init), waypoint_y(waypoint_y_init) {}

    int naviguj(std::string cesta_soubor, bool druhe_reseni) {
        std::ifstream vstup(cesta_soubor);
        if (!vstup.is_open()) {
            std::cerr << "Chyba při otevírání souboru: " << cesta_soubor << std::endl;
            return -1;
        }

        std::string instrukce;
        while (std::getline(vstup, instrukce)) {
            char akce = instrukce[0];
            int hodnota = std::stoi(instrukce.substr(1));

            if (druhe_reseni) {
                if (akce == 'N') waypoint_y += hodnota;
                else if (akce == 'S') waypoint_y -= hodnota;
                else if (akce == 'E') waypoint_x += hodnota;
                else if (akce == 'W') waypoint_x -= hodnota;
                else if (akce == 'L' || akce == 'R') otoc_waypoint(akce, hodnota);
                else if (akce == 'F') {
                    x += hodnota * waypoint_x;
                    y += hodnota * waypoint_y;
                }
            } else {
                if (akce == 'N') y += hodnota;
                else if (akce == 'S') y -= hodnota;
                else if (akce == 'E') x += hodnota;
                else if (akce == 'W') x -= hodnota;
                else if (akce == 'L' || akce == 'R') otoc_lod(akce, hodnota);
                else if (akce == 'F') pohyb_vpred(hodnota);
            }
        }
        vstup.close();

        return std::abs(x) + std::abs(y);
    }

private:
    void otoc_lod(char akce, int stupne) {
        int nasobek = (akce == 'L' ? -1 : 1);
        int nove_smerovani = ((smer_to_deg(smer) + nasobek * stupne) % 360 + 360) % 360;
        smer = deg_to_smer(nove_smerovani);
    }

    void otoc_waypoint(char akce, int stupne) {
        int nasobek = (akce == 'L' ? 1 : -1);
        int rotace = ((nasobek * stupne) % 360 + 360) % 360;
        int nove_x = waypoint_x, nove_y = waypoint_y;

        if (rotace == 90) {
            nove_x = -waypoint_y;
            nove_y = waypoint_x;
        } else if (rotace == 180) {
            nove_x = -waypoint_x;
            nove_y = -waypoint_y;
        } else if (rotace == 270) {
            nove_x = waypoint_y;
            nove_y = -waypoint_x;
        }

        waypoint_x = nove_x;
        waypoint_y = nove_y;
    }

    void pohyb_vpred(int hodnota) {
        if (smer == 'N') y += hodnota;
        else if (smer == 'S') y -= hodnota;
        else if (smer == 'E') x += hodnota;
        else if (smer == 'W') x -= hodnota;
    }

    int smer_to_deg(char smer) {
        if (smer == 'E') return 0;
        if (smer == 'N') return 90;
        if (smer == 'W') return 180;
        if (smer == 'S') return 270;
        return 0;
    }

    char deg_to_smer(int stupne) {
        if (stupne == 0) return 'E';
        if (stupne == 90) return 'N';
        if (stupne == 180) return 'W';
        if (stupne == 270) return 'S';
        return 'E';
    }
};

#ifndef __TEST__
int main() {
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << "Vzdálenost bez waypointu: " << lod.naviguj("vstup_1.txt", false) << std::endl;

    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << "Vzdálenost s waypointem: " << lod2.naviguj("vstup_1.txt", true) << std::endl;

    return 0;
}
#endif // __TEST__

*/