//Importy
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
//Kód velmi komentovaný   (Přečíst jak Rus[Vtip])
//Třída
class Lod {
private:
    //data types a Proměné + Explanation
    int x, y;             // Pozice lodi (souřadnice X a Y)
    char smer;            // Směr lodi (N = North, E = East, S = South, W = West)
    int waypointX, waypointY; // Souřadnice waypointu relativně vůči lodi (pro druhé řešení)

    // Otáčení lodi o 90° vpravo (R) nebo vlevo (L) pro první část (změna směru lodi, nikoliv waypointu)
    void otocSmer(char smerOtoceni, int stupne) {
        int kroky = (stupne / 90) % 4; // Počet kroků o 90° (1 krok = 90°)
        if (smerOtoceni == 'L') kroky = 4 - kroky; // Pokud je otočení doleva počet kroků invertujeme

        const char smery[] = {'N', 'E', 'S', 'W'}; // Sekvence směrů ve směru hodinových ručiček
        int index = 0;
        for (int i = 0; i < 4; ++i) { // Najdeme aktuální index směru
            if (smery[i] == smer) {
                index = i;
                break;
            }
        }
        smer = smery[(index + kroky) % 4]; // Nastavíme nový směr podle počtu kroků/asi přístě udělám vojenské dvojkroky for the plot
    }

    // Otočení waypointu pro druhé řešení protože úkol má podúkol
    void otocWaypoint(char smerOtoceni, int stupne) {
        int kroky = (stupne / 90) % 4; // Počet kroků otočení o 90° já když pořadovka
        if (smerOtoceni == 'L') kroky = 4 - kroky; // LevoBok
        while (kroky--) { // Otočení waypointu po 90° ve směru hodinových ručiček
            int temp = waypointX;
            waypointX = waypointY;
            waypointY = -temp;
        }
    }

    // Pohyb lodi nebo waypointu na základě příkazu
    void pohni(char akce, int hodnota, bool druheReseni) {
        if (akce == 'N' || akce == 'S' || akce == 'E' || akce == 'W') {
            // Pohyb ve směru (N, S, E, W) - buď lodi nebo waypointu podle řešení
            int dx = 0, dy = 0;
            switch (akce) {
                case 'N': dy = hodnota; break;
                case 'S': dy = -hodnota; break;
                case 'E': dx = hodnota; break;
                case 'W': dx = -hodnota; break;
            }
            if (druheReseni) { // Pro druhé řešení upravíme pozici waypointu
                waypointX += dx;
                waypointY += dy;
            } else { // Pro první řešení upravíme pozici lodi
                x += dx;
                y += dy;
            }
        }
        else if (akce == 'L' || akce == 'R') {
            // Otočení - buď lodi nebo waypointu podle řešení
            if (druheReseni) {
                otocWaypoint(akce, hodnota);
            } else {
                otocSmer(akce, hodnota); // První část otáčí pouze směr lodi
            }
        }
        else if (akce == 'F') {
            // Pohyb kupředu - buď podle směru lodi (první řešení) nebo směrem k waypointu (druhé řešení)
            if (druheReseni) {
                x += waypointX * hodnota; // Loď se přesune k waypointu hodnota-krát
                y += waypointY * hodnota;
            } else {
                // Pohyb podle směru lodi (N, S, E, W)
                switch (smer) {
                    case 'N': y += hodnota; break;
                    case 'S': y -= hodnota; break;
                    case 'E': x += hodnota; break;
                    case 'W': x -= hodnota; break;
                }
            }
        }
    }

public:
    // Konstruktor nastavující počáteční pozici lodi směr a relativní pozici waypointu
    Lod(int startX, int startY, char startSmer, int waypointXRel, int waypointYRel)
            : x(startX), y(startY), smer(startSmer), waypointX(waypointXRel), waypointY(waypointYRel) {}

    // Funkce naviguj načítá příkazy ze souboru a pohybuje lodí podle nich
    int naviguj(const std::string& cestaSoubor, bool druheReseni) {
        std::ifstream vstup(cestaSoubor); // Načítáme vstupní soubor
        if (!vstup.is_open()) { // Kontrola zda se soubor otevřel
            std::cerr << "Nepodařilo se otevřít soubor: " << cestaSoubor << std::endl; //Nefunguje toooo **\Ukoly2024\advent_lod.exe tady do složky to musí být se obávám
            return -1; // Vrátí chybu pokud soubor neexistuje nebo nejde otevřít
        }

        std::string line;
        while (std::getline(vstup, line)) { // Načítáme příkazy po řádcích
            char akce = line[0]; // První znak řádky je akce
            int hodnota = std::stoi(line.substr(1)); // Zbytek řádky je hodnota
            pohni(akce, hodnota, druheReseni); // Provádíme pohyb podle akce a hodnoty
        }

        vstup.close(); // Zavřeme soubor po přečtení všech příkazů
        return std::abs(x) + std::abs(y); // Vracíme Manhattan vzdálenost od počátečního bodu (0,0)
    }
};

#ifndef __TEST__ // Podmíněná kompilace hlavní funkce
int main() {
    Lod lod(0, 0, 'E', 10, 1); // Vytvoří instanci lodi pro první řešení
    std::cout << lod.naviguj("vstup_1.txt", false) << std::endl; // Naviguje podle prvního řešení

    Lod lod2(0, 0, 'E', 10, 1); // Vytvoří instanci lodi pro druhé řešení
    std::cout << lod2.naviguj("vstup_1.txt", true) << std::endl; // Naviguje podle druhého řešení

    return 0;
}
#endif // __TEST__

/**Fun fact:
První počítačový virus se nazýval Creeper
a byl vytvořen v roce 1971. Tento virus se šířil po síti ARPANET a zobrazoval zprávu:
"I'm the creeper, catch me if you can!".        **/

/**
 * Komentáře k testovacím vstupům:
 * Vstup 1 - první pokus 3241 po úpravě 379; Výstup: 7085
 * Vstup 2 - první pokus 289 po úpravě 41; Výstup: 587
 * Vstup 3 - první pokus 3977 po úpravě 707; Výstup: 27542

** Nevím jestli jsem nervózní protože nevím kolik to má vyjít xd ** Copyright @Zdénálovo Panství s.r.o. Founded By Kapitán Lord Zdenál. **
**/