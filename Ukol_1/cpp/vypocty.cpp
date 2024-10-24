// #include "vypocty.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>  // Pro std::sort

int soucet(const std::vector<int> &cisla)       //hello
{
    return std::accumulate(cisla.begin(), cisla.end(), 0);
}

int soucin(const std::vector<int> &cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 1, std::multiplies<int>());
}

double prumer(const std::vector<int> &cisla)
{
    if (cisla.empty()) {
        return 0; 
    }

    int soucet = std::accumulate(cisla.begin(), cisla.end(), 0);

    return static_cast<double>(soucet) / cisla.size();
}

double median(const std::vector<int> &cisla)
{
    if (cisla.empty()) {
        return 0; 
    }

    std::sort(cisla.begin(), cisla.end());

    size_t size = cisla.size();

    if (size % 2 != 0) {
        return cisla[size / 2];
    }

    else {
        return (cisla[size / 2 - 1] + cisla[size / 2]) / 2.0;
    }
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    // TODO: Načtěte čísla ze vstupu do vektoru cisla

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__
