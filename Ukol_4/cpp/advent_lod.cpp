#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

class Lod
{
private:
    // Souřadnice lodi
    int x_;
    int y_;

    // Orientace lodi ve stupních, kde:
    //   0   = North (N)
    //   90  = East  (E)
    //   180 = South (S)
    //   270 = West  (W)
    int orientation_;

    // Waypoint (relativní souřadnice vůči lodi) pro 2. část
    int waypoint_x_;
    int waypoint_y_;

    /**
     * Pomocná funkce pro převod znaku (N, S, E, W) na úhel.
     * Zde zvoleno mapování:
     *   N ->   0 °
     *   E ->  90 °
     *   S -> 180 °
     *   W -> 270 °
     */
    static int directionToDegrees(char dir)
    {
        switch(dir) {
            case 'N': return 0;
            case 'E': return 90;
            case 'S': return 180;
            case 'W': return 270;
        }
        // Pokud náhodou není zadáno nic z výše uvedeného, vrátíme 90 (East)
        return 90;
    }

    /**
     * Otočení doleva o daný počet stupňů (u části 1).
     */
    void turnLeft(int deg)
    {
        orientation_ = (orientation_ - deg + 360) % 360;
    }

    /**
     * Otočení doprava o daný počet stupňů (u části 1).
     */
    void turnRight(int deg)
    {
        orientation_ = (orientation_ + deg) % 360;
    }

    /**
     * Pohyb lodi vpřed o danou vzdálenost ve směru orientation_ (u části 1).
     */
    void moveForward(int value)
    {
        switch(orientation_) {
            case 0:   // North
                y_ += value;
                break;
            case 90:  // East
                x_ += value;
                break;
            case 180: // South
                y_ -= value;
                break;
            case 270: // West
                x_ -= value;
                break;
        }
    }

    /**
     * Rotace waypointu (waypoint_x_, waypoint_y_) kolem bodu (0,0) 
     * o `deg` stupňů doprava (pro část 2).
     *
     * Příklad:
     *  - otočení o 90 stupňů doprava: (x, y) -> (y, -x)
     *  - otočení o 180 stupňů: (x, y) -> (-x, -y)
     *  - otočení o 270 stupňů doprava: (x, y) -> (-y, x)
     *
     * Pro otočení doleva o `val` lze použít otočení doprava o `360 - val`.
     */
    void rotateWaypoint(int deg)
    {
        // Normalizace na 0..359
        deg = (deg + 360) % 360;

        int old_x = waypoint_x_;
        int old_y = waypoint_y_;

        switch (deg) {
            case 0:
                // Bez rotace
                break;
            case 90:
                waypoint_x_ = old_y;
                waypoint_y_ = -old_x;
                break;
            case 180:
                waypoint_x_ = -old_x;
                waypoint_y_ = -old_y;
                break;
            case 270:
                waypoint_x_ = -old_y;
                waypoint_y_ = old_x;
                break;
        }
    }

public:
    /**
     * Konstruktor lodi.
     *
     * @param x počáteční souřadnice x
     * @param y počáteční souřadnice y
     * @param smer počáteční směr lodi (N, S, E, W)
     * @param cilovy_bod_x počáteční x-ová souřadnice waypointu (relativně k lodi)
     * @param cilovy_bod_y počáteční y-ová souřadnice waypointu (relativně k lodi)
     */
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
        : x_(x),
          y_(y),
          orientation_(directionToDegrees(smer)),
          waypoint_x_(cilovy_bod_x),
          waypoint_y_(cilovy_bod_y)
    {
    }

    /**
     * Metoda pro zpracování navigačních instrukcí.
     *
     * @param cesta_soubor Cesta k souboru s instrukcemi
     * @param druhe_reseni Pokud je true, použije se waypoint (část 2), jinak část 1.
     * @return Manhattan distance od počáteční pozice (0,0) po zpracování všech instrukcí
     */
    int naviguj(const std::string &cesta_soubor, bool druhe_reseni)
    {
        std::ifstream in(cesta_soubor);
        if (!in.is_open()) {
            std::cerr << "Chyba při otevírání souboru " << cesta_soubor << std::endl;
            return 0;
        }

        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) {
                continue;
            }
            // První znak je příkaz (např. 'F', 'N', 'R', ...)
            char cmd = line[0];
            // Ostatní znaky jsou číselná hodnota (např. 10, 3, 90, ...)
            int value = std::stoi(line.substr(1));

            if (!druhe_reseni)
            {
                // --- ČÁST 1: jednoduchý pohyb bez waypointu ---
                switch (cmd) {
                    case 'N': y_ += value; break;
                    case 'S': y_ -= value; break;
                    case 'E': x_ += value; break;
                    case 'W': x_ -= value; break;
                    case 'L': turnLeft(value);  break;
                    case 'R': turnRight(value); break;
                    case 'F': moveForward(value); break;
                }
            }
            else
            {
                // --- ČÁST 2: s použitím waypointu ---
                switch (cmd) {
                    case 'N': waypoint_y_ += value; break;
                    case 'S': waypoint_y_ -= value; break;
                    case 'E': waypoint_x_ += value; break;
                    case 'W': waypoint_x_ -= value; break;
                    case 'L':
                        // Otočení waypointu doleva o 'value' je totéž co doprava o (360 - value)
                        rotateWaypoint(360 - value);
                        break;
                    case 'R':
                        rotateWaypoint(value);
                        break;
                    case 'F':
                        // Posun lodi o 'value' násobků waypointu
                        x_ += waypoint_x_ * value;
                        y_ += waypoint_y_ * value;
                        break;
                }
            }
        }

        // Manhattan distance od počátečního bodu (0,0)
        return std::abs(x_) + std::abs(y_);
    }
};

#ifndef __TEST__
int main()
{
    // 1) Spuštění bez waypointu (část 1)
    Lod lod(0, 0, 'E', 10, 1);
    int vzdalenost_1 = lod.naviguj("vstup_1.txt", false);
    std::cout << "Manhattan vzdálenost (bez waypointu): " << vzdalenost_1 << std::endl;

    // 2) Spuštění s waypointem (část 2)
    Lod lod2(0, 0, 'E', 10, 1);
    int vzdalenost_2 = lod2.naviguj("vstup_1.txt", true);
    std::cout << "Manhattan vzdálenost (s waypointem):   " << vzdalenost_2 << std::endl;

    return 0;
}
#endif // __TEST__
