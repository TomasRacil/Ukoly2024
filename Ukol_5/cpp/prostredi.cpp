#include "prostredi.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Prostredi::Prostredi(int w, int h) : width(w), height(h) {
    srand(time(0)); 
}

void Prostredi::pridejZivocicha(const Zivocich &z) {
    zivocichove.push_back(z);
}

void Prostredi::pridejRostlinu(const Rostlina &r) {
    rostliny.push_back(r);
}

void Prostredi::simuluj(int kroky) {
    for (int i = 0; i < kroky; ++i) {
        for (auto &z : zivocichove) {
            z.pohyb();
            for (auto &r : rostliny) {
                z.konzumace(r);
            }
        }
        rozmnozovani();
        zobrazStav();
    }
    zobrazEnergie();
}

void Prostredi::rozmnozovani() {
    std::vector<Zivocich> noveZivocichove;
    for (size_t i = 0; i < zivocichove.size(); ++i) {
        for (size_t j = i + 1; j < zivocichove.size(); ++j) {
            if (zivocichove[i].getX() == zivocichove[j].getX() && zivocichove[i].getY() == zivocichove[j].getY()) {
                noveZivocichove.push_back(Zivocich(zivocichove[i].getX(), zivocichove[i].getY(), 10));
            }
        }
    }
    zivocichove.insert(zivocichove.end(), noveZivocichove.begin(), noveZivocichove.end());
}

void Prostredi::zobrazStav() {
    std::vector<std::vector<char>> mrizka(width, std::vector<char>(height, '.'));
    for (auto &r : rostliny) {
        if (r.getEnergie() > 0) {
            mrizka[r.getX()][r.getY()] = 'X';
        }
    }
    for (auto &z : zivocichove) {
        if (mrizka[z.getX()][z.getY()] == 'X') {
            mrizka[z.getX()][z.getY()] = '@'; 
        } else {
            mrizka[z.getX()][z.getY()] = 'O';
        }
    }
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            std::cout << mrizka[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "--------" << std::endl;
}

void Prostredi::zobrazEnergie() {
    std::cout << "Energeticke stavy zivocichu na konci simulace:" << std::endl;
    for (size_t i = 0; i < zivocichove.size(); ++i) {
        std::cout << "Zivocich " << (i + 1) << ": Energie = " << zivocichove[i].getEnergie() << std::endl;
    }
}
