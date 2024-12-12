#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>  

int soucet(const std::vector<int>& cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 0);
}

int soucin(const std::vector<int>& cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 1, std::multiplies<int>());
}

double prumer(const std::vector<int>& cisla)
{
    if (cisla.empty()) {
        throw std::invalid_argument("Prázdný seznam");
    }
    int soucet = std::accumulate(cisla.begin(), cisla.end(), 0);
    return static_cast<double>(soucet) / cisla.size();
}

double median(const std::vector<int>& cisla)
{
    if (cisla.empty()) {
        throw std::invalid_argument("Prázdný seznam");
    }
    std::vector<int> sorted_cisla = cisla;
    std::sort(sorted_cisla.begin(), sorted_cisla.end());
    size_t size = sorted_cisla.size();

    if (size % 2 != 0) {
        return sorted_cisla[size / 2];
    } else {
        return (sorted_cisla[size / 2 - 1] + sorted_cisla[size / 2]) / 2.0;
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
#endif // __TEST__
