#include <iostream>
#include <fstream>

class Lod {
private:
    int x;
    int y;
    char smer;
    int cilovy_bod_x;
    int cilovy_bod_y;


    void reseni1(char akce, int hodnota) {
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
            case 'L':
                for (int i = 0; i < hodnota / 90; i++) {
                    if (smer == 'N') {
                        smer = 'W';
                    } else if (smer == 'W') {
                        smer = 'S';
                    } else if (smer == 'S') {
                        smer = 'E';
                    } else if (smer == 'E') {
                        smer = 'N';
                    }
                }
                break;
            case 'R':
                for (int i = 0; i < hodnota / 90; i++) {
                    if (smer == 'N') {
                        smer = 'E';
                    } else if (smer == 'E') {
                        smer = 'S';
                    } else if (smer == 'S') {
                        smer = 'W';
                    } else if (smer == 'W') {
                        smer = 'N';
                    }
                }
                break;
            case 'F':
                if (smer == 'N') {
                    y += hodnota;
                } else if (smer == 'S') {
                    y -= hodnota;
                } else if (smer == 'E') {
                    x += hodnota;
                } else if (smer == 'W') {
                    x -= hodnota;
                }
                break;
        }
    }

    void otocit(int uhel) {
        if (uhel < 0) {
            uhel = 360 + uhel;
        }
        int pocet_otoceni = uhel / 90;
        for (int i = 0; i < pocet_otoceni; i++) {
            int temp = cilovy_bod_x;
            cilovy_bod_x = cilovy_bod_y;
            cilovy_bod_y = -temp;
        }
    }

    void reseni2(char akce, int hodnota) {
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
                otocit(-hodnota);
                break;
            case 'R':
                otocit(hodnota);
                break;
            case 'F':
                x += hodnota * cilovy_bod_x;
                y += hodnota * cilovy_bod_y;
                break;
        }
    }

public:
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
            : x(x), y(y), smer(smer), cilovy_bod_x(cilovy_bod_x), cilovy_bod_y(cilovy_bod_y) {
    }

    int naviguj(std::string cesta_soubor, bool druhe_reseni) {
        std::ifstream soubor(cesta_soubor);
        if (!soubor.is_open()) {
            return -1;
        }

        int original_x = x;
        int original_y = y;

        std::string radek;
        while (std::getline(soubor, radek)) {
            char akce = radek[0];
            int hodnota = std::stoi(radek.substr(1));

            if (!druhe_reseni) {
                reseni1(akce, hodnota);
            } else {
                reseni2(akce, hodnota);
            }
        }

        int manhattan_vzdalenost = std::abs(x - original_x) + std::abs(y - original_y);

        return manhattan_vzdalenost;
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