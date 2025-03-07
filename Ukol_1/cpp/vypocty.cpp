#include "vypocty.h"
#include <iostream>
#include <vector>
#include <algorithm> // kvůli std::sort
#include <sstream>   // kvůli std::stringstream

int soucet(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci
    int vysledek = 0;
    for (int c : cisla) {
        vysledek += c;
    }
    return vysledek;
}

int soucin(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci

    int vysledek = 1;
    for (int c : cisla) {
        vysledek *= c;
    }
    return vysledek;
}

double prumer(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci

    double suma = 0.0;
    for (int c : cisla) {
        suma += c;
    }
    return suma / cisla.size();
}

double median(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci

    std::vector<int> kopie = cisla;
    std::sort(kopie.begin(), kopie.end());

    int n = kopie.size();
    if (n % 2 == 1) {
        // pokud je počet prvků lichý
        return kopie[n / 2];
    } else {
        // pokud je počet prvků sudý
        return (kopie[n / 2 - 1] + kopie[n / 2]) / 2.0;
    }
}

#ifndef __TEST__
int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    // TODO: Načtěte čísla ze vstupu do vektoru cisla
    {
        std::stringstream ss(vstup);
        std::string hodnota;
        while (std::getline(ss, hodnota, ',')) {
            if (!hodnota.empty()) {
                cisla.push_back(std::stoi(hodnota));
            }
        }
    }

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__
