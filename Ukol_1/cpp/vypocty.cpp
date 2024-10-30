#include <iostream>
#include <vector>

int soucet(const std::vector<int> &cisla)
{
    int soucet = 0;
    for (int cislo : cisla) {
        soucet += cislo;
    }
    return soucet;
}

int soucin(const std::vector<int> &cisla)
{
    if (cisla.empty()) return 1;
    int soucin = 1;
    for (int cislo : cisla) {
        soucin *= cislo;
    }
    return soucin;
}

double prumer(const std::vector<int> &cisla)
{
    if (cisla.empty()) throw std::invalid_argument("prazdny seznam");
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

double median(const std::vector<int> &cisla)
{
    if (cisla.empty()) throw std::invalid_argument("Prázdný seznam.");
    
    std::vector<int> kopie = cisla; 
    size_t n = kopie.size();


    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (kopie[j] > kopie[j + 1]) {
                int temp = kopie[j];
                kopie[j] = kopie[j + 1];
                kopie[j + 1] = temp;
            }
        }
    }

    if (n % 2 == 0) {
        return (kopie[n / 2 - 1] + kopie[n / 2]) / 2.0;
    } else {
        return kopie[n / 2];
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