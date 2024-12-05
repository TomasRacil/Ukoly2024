#include <iostream>  // Pro vstup a výstup
#include <fstream>   // Pro práci se soubory
#include <vector>    // Pro použití vektorů
#include <cmath>     // Pro matematické funkce, jako je abs()

//komentáře slouží k vysvětlení kódu a samostudiu


class Lod
{
private:
    int x, y;  // Souřadnice lodi
    char smer;  // Směr, kterým loď směřuje
    int cilovy_bod_x, cilovy_bod_y;  // Souřadnice waypointu relativně k lodi

    void otocDoleva(int stupne)  // Otočení lodi doleva o daný počet stupňů
    {
        for (int i = 0; i < stupne / 90; ++i)  // Pro každý 90° krok
        {
            switch (smer)  // Změna směru lodi
            {
            case 'N': smer = 'W'; break;  // Ze severu na západ
            case 'W': smer = 'S'; break;  // Ze západu na jih
            case 'S': smer = 'E'; break;  // Z jihu na východ
            case 'E': smer = 'N'; break;  // Z východu na sever
            }
        }
    }

    void otocDoprava(int stupne)  // Otočení lodi doprava o daný počet stupňů
    {
        for (int i = 0; i < stupne / 90; ++i)  // Pro každý 90° krok
        {
            switch (smer)  // Změna směru lodi
            {
            case 'N': smer = 'E'; break;  // Ze severu na východ
            case 'E': smer = 'S'; break;  // Z východu na jih
            case 'S': smer = 'W'; break;  // Z jihu na západ
            case 'W': smer = 'N'; break;  // Ze západu na sever
            }
        }
    }

    void pohybVpřed(int hodnota)  // Pohyb lodi vpřed o daný počet jednotek
    {
        switch (smer)  // Podle aktuálního směru
        {
        case 'N': y += hodnota; break;  // Pohyb na sever
        case 'S': y -= hodnota; break;  // Pohyb na jih
        case 'E': x += hodnota; break;  // Pohyb na východ
        case 'W': x -= hodnota; break;  // Pohyb na západ
        }
    }

    void pohybWaypointem(char akce, int hodnota)  // Pohyb waypointem
    {
        switch (akce)  // Podle akce
        {
        case 'N': cilovy_bod_y += hodnota; break;  // Pohyb waypointem na sever
        case 'S': cilovy_bod_y -= hodnota; break;  // Pohyb waypointem na jih
        case 'E': cilovy_bod_x += hodnota; break;  // Pohyb waypointem na východ
        case 'W': cilovy_bod_x -= hodnota; break;  // Pohyb waypointem na západ
        }
    }

    void otocWaypointDoleva(int stupne)  // Otočení waypointu doleva
    {
        for (int i = 0; i < stupne / 90; ++i)  // Pro každý 90° krok
        {
            int temp = cilovy_bod_x;  // Dočasná proměnná pro otočení
            cilovy_bod_x = -cilovy_bod_y;  // Otočení souřadnic
            cilovy_bod_y = temp;  // Otočení souřadnic
        }
    }

    void otocWaypointDoprava(int stupne)  // Otočení waypointu doprava
    {
        for (int i = 0; i < stupne / 90; ++i)  // Pro každý 90° krok
        {
            int temp = cilovy_bod_x;  // Dočasná proměnná pro otočení
            cilovy_bod_x = cilovy_bod_y;  // Otočení souřadnic
            cilovy_bod_y = -temp;  // Otočení souřadnic
        }
    }

    void pohybKWaypointu(int hodnota)  // Pohyb lodi směrem k waypointu
    {
        x += cilovy_bod_x * hodnota;  // Aktualizace souřadnic lodi
        y += cilovy_bod_y * hodnota;  // Aktualizace souřadnic lodi
    }

public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)  // Konstruktor třídy Lod
        : x(x), y(y), smer(smer), cilovy_bod_x(cilovy_bod_x), cilovy_bod_y(cilovy_bod_y) {}

    int naviguj(std::string cesta_soubor, bool druhe_reseni)  // Funkce pro navigaci lodi
    {
        std::ifstream inputFile(cesta_soubor);  // Otevření vstupního souboru
        std::vector<std::string> instrukce;  // Vektor pro uložení instrukcí
        std::string line;  // Proměnná pro čtení řádků

        while (std::getline(inputFile, line))  // Čtení instrukcí ze souboru
        {
            instrukce.push_back(line);  // Uložení instrukce do vektoru
        }

        for (const auto &instr : instrukce)  // Zpracování každé instrukce
        {
            char akce = instr[0];  // Akce (první znak instrukce)
            int hodnota = std::stoi(instr.substr(1));  // Hodnota (zbytek instrukce)

            if (druhe_reseni)  // Pokud je aktivní druhé řešení
            {
                switch (akce)  // Zpracování akce
                {
                case 'N': case 'S': case 'E': case 'W': pohybWaypointem(akce, hodnota); break;  // Pohyb waypointem
                case 'L': otocWaypointDoleva(hodnota); break;  // Otočení waypointu doleva
                case 'R': otocWaypointDoprava(hodnota); break;  // Otočení waypointu doprava
                case 'F': pohybKWaypointu(hodnota); break;  // Pohyb lodi k waypointu
                }
            }
            else  // Pokud je aktivní první řešení
            {
                switch (akce)  // Zpracování akce
                {
                case 'N': y += hodnota; break;  // Pohyb na sever
                case 'S': y -= hodnota; break;  // Pohyb na jih
                case 'E': x += hodnota; break;  // Pohyb na východ
                case 'W': x -= hodnota; break;  // Pohyb na západ
                case 'L': otocDoleva(hodnota); break;  // Otočení doleva
                case 'R': otocDoprava(hodnota); break;  // Otočení doprava
                case 'F': pohybVpřed(hodnota); break;  // Pohyb vpřed
                }
            }
        }

        return std::abs(x) + std::abs(y);  // Výpočet Manhattan vzdálenosti
    }
};

#ifndef __TEST__
int main() 
{
    Lod lod(0, 0, 'E', 10, 1);  // Vytvoření instance lodi
    std::cout << "Manhattan vzdálenost: " << lod.naviguj("vstup_1.txt", false) << std::endl;  // Navigace lodi podle prvního řešení
    Lod lod2(0, 0, 'E', 10, 1);  // Vytvoření druhé instance lodi
    std::cout << "Manhattan vzdálenost s waypointem: " << lod2.naviguj("vstup_1.txt", true) << std::endl;  // Navigace lodi podle druhého řešení
    return 0;  
}
#endif // __TEST__
