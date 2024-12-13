#include <vector>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <iostream>

int soucet(const std::vector<int>& cisla) {
    return std::accumulate(cisla.begin(), cisla.end(), 0);
}

int soucin(const std::vector<int>& cisla) {
    if (cisla.empty()) return 1; // Prázdný seznam vrací 1
    return std::accumulate(cisla.begin(), cisla.end(), 1, std::multiplies<int>());
}

double prumer(const std::vector<int>& cisla) {
    if (cisla.empty()) throw std::invalid_argument("Seznam je prázdný");
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

double median(std::vector<int> cisla) {
    if (cisla.empty()) throw std::invalid_argument("Seznam je prázdný");
    std::sort(cisla.begin(), cisla.end());
    size_t n = cisla.size();
    if (n % 2 == 0) {
        return (cisla[n / 2 - 1] + cisla[n / 2]) / 2.0;
    } else {
        return cisla[n / 2];
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

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif 