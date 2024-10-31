#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

int soucet(const std::vector<int> &cisla) {
    return std::accumulate(cisla.begin(), cisla.end(), 0);
}

int soucin(const std::vector<int> &cisla) {
    int soucin = 1;
    for (int cislo : cisla) {
        soucin *= cislo;
    }
    return soucin;
}

double prumer(const std::vector<int> &cisla) {
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

double median(std::vector<int> cisla) {
    std::sort(cisla.begin(), cisla.end());
    int n = cisla.size();
    if (n % 2 == 0) {
        return (cisla[n / 2 - 1] + cisla[n / 2]) / 2.0;
    } else {
        return cisla[n / 2];
    }
}

int main() {
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::stringstream ss(vstup);
    std::string hodnota;

    while (std::getline(ss, hodnota, ',')) {
        cisla.push_back(std::stoi(hodnota));
    }

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
