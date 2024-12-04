#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Funkce pro výpočet součtu
int soucet(const std::vector<int> &cisla) {
    int suma = 0;
    for (int cislo : cisla) {
        suma += cislo;
    }
    return suma;
}

// Funkce pro výpočet součinu
int soucin(const std::vector<int> &cisla) {
    int produkt = 1;
    for (int cislo : cisla) {
        produkt *= cislo;
    }
    return produkt;
}

// Funkce pro výpočet průměrné hodnoty
double prumer(const std::vector<int> &cisla) {
    if (cisla.empty()) {
        return 0.0; // Ochrana proti dělení nulou
    }
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

// Funkce pro výpočet mediánu
double median(std::vector<int> cisla) {
    if (cisla.empty()) {
        return 0.0;
    }

    std::sort(cisla.begin(), cisla.end());
    size_t velikost = cisla.size();

    if (velikost % 2 == 0) {
        return (cisla[velikost / 2 - 1] + cisla[velikost / 2]) / 2.0;
    } else {
        return cisla[velikost / 2];
    }
}

#ifndef __TEST__ 
int main() {
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::stringstream ss(vstup);
    std::string token;
    while (std::getline(ss, token, ',')) {
        cisla.push_back(std::stoi(token));
    }

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__