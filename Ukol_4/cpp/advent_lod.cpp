#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

class Lod {
private:
    int x, y;                // Souřadnice lodi
    int smer;                // Směr lodi ve stupních (0 = východ, 90 = sever, 180 = západ, 270 = jih)
    int waypoint_x, waypoint_y; // Souřadnice waypointu relativní k lodi

public:
    // Konstruktor pro Část 1 (výchozí směr na východ)
    Lod() : x(0), y(0), smer(0) {}

    // Konstruktor pro Část 2 s waypointem
    Lod(int wp_x, int wp_y) : x(0), y(0), waypoint_x(wp_x), waypoint_y(wp_y) {}

    // Otočení lodi vlevo nebo vpravo ve stupních
    void otocLod(char direction, int degrees) {
        smer = (smer + (direction == 'L' ? degrees : 360 - degrees)) % 360;
    }

    // Otočení waypointu kolem lodi (Část 2)
    void otocWaypoint(char direction, int degrees) {
        int rotations = (direction == 'L' ? degrees : 360 - degrees) / 90;
        for (int i = 0; i < rotations; ++i) {
            int temp = waypoint_x;
            waypoint_x = -waypoint_y;
            waypoint_y = temp;
        }
    }

    // Posun lodi v aktuálním směru (pouze pro Část 1)
    void posunVpřed(int jednotky) {
        switch (smer) {
            case 0: x += jednotky; break;   // Východ
            case 90: y += jednotky; break;  // Sever
            case 180: x -= jednotky; break; // Západ
            case 270: y -= jednotky; break; // Jih
        }
    }

    // Pohyb lodi směrem k waypointu (Část 2)
    void posunKWaypointu(int jednotky) {
        x += waypoint_x * jednotky;
        y += waypoint_y * jednotky;
    }

    // Metoda pro navigaci podle souboru instrukcí
    int naviguj(const std::string &soubor, bool s_waypointem) {
        std::ifstream infile(soubor);
        if (!infile) {
            std::cerr << "Nepodarilo se otevrit soubor." << std::endl;
            return -1;
        }

        std::string instrukce;
        while (std::getline(infile, instrukce)) {
            char akce = instrukce[0];
            int hodnota = std::stoi(instrukce.substr(1));

            if (s_waypointem) { // Část 2: navigace s waypointem
                switch (akce) {
                    case 'N': waypoint_y += hodnota; break;
                    case 'S': waypoint_y -= hodnota; break;
                    case 'E': waypoint_x += hodnota; break;
                    case 'W': waypoint_x -= hodnota; break;
                    case 'L': otocWaypoint('L', hodnota); break;
                    case 'R': otocWaypoint('R', hodnota); break;
                    case 'F': posunKWaypointu(hodnota); break;
                }
            } else { // Část 1: klasická navigace
                switch (akce) {
                    case 'N': y += hodnota; break;
                    case 'S': y -= hodnota; break;
                    case 'E': x += hodnota; break;
                    case 'W': x -= hodnota; break;
                    case 'L': otocLod('L', hodnota); break;
                    case 'R': otocLod('R', hodnota); break;
                    case 'F': posunVpřed(hodnota); break;
                }
            }
        }

        // Vracíme Manhattan vzdálenost
        return std::abs(x) + std::abs(y);
    }
};

#ifndef __TEST__
int main() {
    // Část 1: Navigace bez waypointu
    Lod lod1;
    int vzdalenost1 = lod1.naviguj("vstup_1.txt", false);
    std::cout << "Manhattanska vzdalenost po navigaci (Cast 1): " << vzdalenost1 << std::endl;

    // Část 2: Navigace s waypointem (waypoint na pozici 10 na východ a 1 na sever)
    Lod lod2(10, 1);
    int vzdalenost2 = lod2.naviguj("vstup_1.txt", true);
    std::cout << "Manhattanska vzdalenost po navigaci s waypointem (Cast 2): " << vzdalenost2 << std::endl;

    return 0;
}
#endif // __TEST__
