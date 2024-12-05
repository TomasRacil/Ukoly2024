#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include "organismus.h"

class Prostredi {
    int sirka, vyska;
    std::vector<Organismus*> organismy;

public:
    Prostredi(int sirka, int vyska) : sirka(sirka), vyska(vyska) {}

    template <typename T>
    void pridatOrganismus(T* organismus) {
        organismy.push_back(organismus);
    }

    void clearScreen() const {
        std::cout << "\033[2J\033[1;1H"; // Vymaže obrazovku a vrátí kurzor na začátek
    }

    void vykresli() const {
        std::vector<std::vector<char>> matic(vyska, std::vector<char>(sirka, '.'));

        for (const auto& organismus : organismy) {
            if (organismus->isAlive()) {
                int x = organismus->getX();
                int y = organismus->getY();
                if (x >= 0 && x < sirka && y >= 0 && y < vyska) {
                    char znak = '.';
                    if (organismus->getTyp() == "kytka") znak = 'm';
                    else if (organismus->getTyp() == "bylozravec") znak = 'B';
                    else if (organismus->getTyp() == "masozravec") znak = 'M';
                    matic[y][x] = znak;
                }
            }
        }

        for (const auto& radek : matic) {
            for (char cell : radek) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
        std::cout << std::string(30, '-') << '\n';
    }

    void simuluj(int kroky) {
        for (int i = 0; i < kroky; ++i) {
            clearScreen();
            std::cout << "Simulace krok " << i + 1 << ":\n";

            for (auto organismus : organismy) {
                if (!organismus->isAlive()) continue;

                // Pohyb
                organismus->pohyb(sirka, vyska);
                organismus->zmensiZivotnost();

                if (!organismus->isAlive()) {
                    std::cout << organismus->getTyp() << " " << organismus->getID() << " zemřel.\n";
                    continue;
                }

                // Interakce mezi organismy
                for (auto ostatni : organismy) {
                    if (organismus == ostatni || !ostatni->isAlive()) continue;

                    // Býložravec jí rostlinu
                    if (organismus->getTyp() == "bylozravec" && ostatni->getTyp() == "kytka") {
                        if (organismus->getX() == ostatni->getX() && organismus->getY() == ostatni->getY()) {
                            organismus->konzumace(60);
                            ostatni->setEnergie(0);
                            std::cout << "Bylozravec " << organismus->getID() << " snědl rostlinu ID: " 
                                      << ostatni->getID() << " na pozici (" << ostatni->getX() 
                                      << ", " << ostatni->getY() << ")\n";
                            break;
                        }
                    }

                    // Masožravec jí býložravce
                    if (organismus->getTyp() == "masozravec" && ostatni->getTyp() == "bylozravec") {
                        if (organismus->getX() == ostatni->getX() && organismus->getY() == ostatni->getY()) {
                            organismus->konzumace(10);
                            ostatni->setEnergie(0);
                            std::cout << "Masozravec " << organismus->getID() << " ulovil býložravce ID: " 
                                      << ostatni->getID() << " na pozici (" << ostatni->getX() 
                                      << ", " << ostatni->getY() << ")\n";
                            break;
                        }
                    }
                }

                // Rozmnožování
                organismus->rozmnozit(organismy, sirka, vyska);
            }

            // Přidání nové rostliny každých 5 kroků
            if ((i + 1) % 5 == 0) {
                int newX = rand() % sirka;
                int newY = rand() % vyska;
                Rostlina* novaRostlina = new Rostlina(newX, newY);
                organismy.push_back(novaRostlina);
                std::cout << "Vytvořena nová rostlina ID: " << novaRostlina->getID() 
                          << " na pozici (" << newX << ", " << newY << ")\n";
            }

            // Odstranění mrtvých organismů
            organismy.erase(std::remove_if(organismy.begin(), organismy.end(),
                        [](Organismus* o) { return !o->isAlive(); }), organismy.end());

            vykresli();
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Zpoždění 200 ms
        }
    }

    ~Prostredi() {
        for (auto organismus : organismy) {
            delete organismus;
        }
    }
};

#endif
