#include <iostream>
#include <vector>

int soucet(const std::vector<int> &cisla) {
    int sum = 0;
    for (int num : cisla) {
        sum += num;
    }
    return sum;
}

int soucin(const std::vector<int> &cisla) {
    int product = 1;
    for (int num : cisla) {
        product *= num;
    }
    return product;
}

double prumer(const std::vector<int> &cisla) {
    if (cisla.empty()) return 0;
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

double median(std::vector<int> cisla) {
    if (cisla.empty()) return 0;
    for (size_t i = 0; i < cisla.size() - 1; ++i) {
        for (size_t j = 0; j < cisla.size() - i - 1; ++j) {
            if (cisla[j] > cisla[j + 1]) {
                int temp = cisla[j];
                cisla[j] = cisla[j + 1];
                cisla[j + 1] = temp;
            }
        }
    }
    size_t n = cisla.size();
    if (n % 2 == 0) {
        return (cisla[n / 2 - 1] + cisla[n / 2]) / 2.0;
    } else {
        return cisla[n / 2];
    }
}

#ifndef __TEST__
int main() {
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::string cislo;
    for (size_t i = 0; i < vstup.size(); ++i) {
        if (vstup[i] == ',') {
            cisla.push_back(std::stoi(cislo));
            cislo.clear();
        } else {
            cislo += vstup[i];
        }
    }
    if (!cislo.empty()) {
        cisla.push_back(std::stoi(cislo));
    }

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__
