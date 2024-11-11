#include <iostream>
#include <fstream>

class Lod {
    //Kapitan lodi: Daniel Bilek :D
    int x;
    int y;
    char smer;
    int cilovy_bod_x;
    int cilovy_bod_y;
public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y) {
        this->x = x;
        this->y = y;
        this->smer = smer;
        this->cilovy_bod_x = cilovy_bod_x;
        this->cilovy_bod_y = cilovy_bod_y;
    }


    int naviguj(std::string cesta_soubor, bool druhe_reseni) {
        std::ifstream soubor(cesta_soubor);
        // Kontrola otevreni souboru
        if (!soubor.is_open()) {
            std::cerr << "Soubor se nepodarilo otevrit / najit" << "Cesta: " << cesta_soubor << std::endl;
            return -1;
        }
        // Kontrola prazdneho souboru
        if (soubor.peek() == std::ifstream::traits_type::eof()) {
            std::cerr << "Soubor je prazdny" << std::endl;
            return -1;
        }
        std::string radek;
        int lineCount = 0;
        while (std::getline(soubor, radek)) {
            lineCount++;
            char akce = radek[0];
            int hodnota = std::stoi(radek.substr(1));
            //Kontrola spravnosti nav. instrukci
            if (akce != 'N' && akce != 'S' && akce != 'E' && akce != 'W' && akce != 'L' && akce != 'R' && akce != 'F') {
                std::cerr << "Neplatna akce. \n Seznam dostupnych akci: N, S, E, W, L, R, F"<<"\nChybna Akce: " << akce << hodnota << " Na Radku: " << lineCount << std::endl;
                return -1;
            }
            //Kontrola spravnosti hodnoty (kladne cislo)
            if (hodnota < 0 ) {
                std::cout << "Hodnota byla prevedena na kladne cislo nelze navigovat zapornym cislem.\n" << std::endl;
                hodnota = abs(hodnota);
            }
            // Kontrola spravnosti hodnoty (pouze 90 stupnu)
            if (akce == 'L' || akce == 'R') {
                if (hodnota % 90 != 0) {
                    std::cerr << "Neplatna akce. \nAkce L/R se musi otacet pouze po 90 stupnich.\nPlatne hodnoty: 0, 90, 180, 360 atd. " <<"\nChybna hodnota: " << akce << hodnota << " Na radku: " << lineCount << std::endl;
                    return -1;
                }
            }
            // Druhe reseni
            if (druhe_reseni) {
                // Pohyb waypointu na svetove strany
                switch (akce) {
                    case 'N':
                        cilovy_bod_y += hodnota;
                        break;
                    case 'S':
                        cilovy_bod_y -= hodnota;
                        break;
                    case 'E':
                        cilovy_bod_x += hodnota;
                        break;
                    case 'W':
                        cilovy_bod_x -= hodnota;
                        break;
                    case 'L':
                        for (int i = 0; i < hodnota / 90; i++) {
                            int temp = cilovy_bod_x;
                            cilovy_bod_x = -cilovy_bod_y;
                            cilovy_bod_y = temp;
                        }
                        break;
                        // Otočení waypointu doprava
                    case 'R':
                        for (int i = 0; i < hodnota / 90; i++) {
                            int temp = cilovy_bod_x;
                            cilovy_bod_x = cilovy_bod_y;
                            cilovy_bod_y = -temp;
                        }
                        break;
                        // Pohyb lodi k waypointu
                    case 'F':
                        x += cilovy_bod_x * hodnota;
                        y += cilovy_bod_y * hodnota;
                        break;
                }

            }
                // Prvni reseni
            else {
                // Pohyb lodi na svetove strany
                switch (akce) {
                    case 'N':
                        y += hodnota;
                        break;
                    case 'S':
                        y -= hodnota;
                        break;
                    case 'E':
                        x += hodnota;
                        break;
                    case 'W':
                        x -= hodnota;
                        break;
                        // Otočení lodi doleva
                    case 'L':
                        for (int i = 0; i < hodnota / 90; i++) {
                            switch (smer) {
                                case 'N':
                                    smer = 'W';
                                    break;
                                case 'W':
                                    smer = 'S';
                                    break;
                                case 'S':
                                    smer = 'E';
                                    break;
                                case 'E':
                                    smer = 'N';
                                    break;
                            }
                        }
                        break;
                        // Otočení lodi doprava
                    case 'R':
                        for (int i = 0; i < hodnota / 90; i++) {
                            switch (smer) {
                                case 'N':
                                    smer = 'E';
                                    break;
                                case 'E':
                                    smer = 'S';
                                    break;
                                case 'S':
                                    smer = 'W';
                                    break;
                                case 'W':
                                    smer = 'N';
                                    break;
                            }
                        }
                        break;
                        // Pohyb lodi vpřed
                    case 'F':
                        switch (smer) {
                            case 'N':
                                y += hodnota;
                                break;
                            case 'S':
                                y -= hodnota;
                                break;
                            case 'E':
                                x += hodnota;
                                break;
                            case 'W':
                                x -= hodnota;
                                break;
                        }
                        break;
                }
            }
        }
        soubor.close();
        //menhattanova vzdalenost
        return abs(x) + abs(y);
    }


};


#ifndef __TEST__

int main() {
    Lod lod(0, 0, 'E', 10, 1);
    std::cout << lod.naviguj("vstup_1.txt", false) << std::endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << lod2.naviguj("vstup_1.txt", true) << std::endl;
    return 0;
}

#endif // __TEST__