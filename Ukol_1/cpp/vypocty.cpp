// #include "vypocty.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>  // Pro std::accumulate

// Funkce pro výpočet součtu čísel
int soucet(const std::vector<int> &cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 0); // Sečte všechna čísla ve vektoru
}

// Funkce pro výpočet součinu čísel
int soucin(const std::vector<int> &cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 1, std::multiplies<int>()); // Vynásobí všechna čísla
}

// Funkce pro výpočet průměru čísel
double prumer(const std::vector<int> &cisla)
{
    return static_cast<double>(soucet(cisla)) / cisla.size(); // Součet dělený počtem prvků
}

// Funkce pro výpočet mediánu
double median(const std::vector<int> &cisla)
{
    std::vector<int> kopie = cisla; // Vytvoříme kopii vektoru, abychom mohli řadit
    std::sort(kopie.begin(), kopie.end()); // Seřadíme čísla
    int n = kopie.size();
    if (n % 2 == 0) // Sudý počet prvků
    {
        return (kopie[n / 2 - 1] + kopie[n / 2]) / 2.0; // Průměr dvou prostředních
    }
    else // Lichý počet prvků
    {
        return kopie[n / 2]; // Prostřední prvek
    }
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::stringstream ss(vstup);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        cisla.push_back(std::stoi(token)); // Převod jednotlivých částí na celá čísla a přidání do vektoru
    }

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__
