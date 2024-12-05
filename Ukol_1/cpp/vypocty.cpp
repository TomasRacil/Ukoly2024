// #include "vypocty.h"
#include <iostream>
#include <vector>
#include <algorithm>

int soucet(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci
    int sum = 0;
    for (int number : cisla) {
        sum += number;
    }
    return sum;
    //return 0;
}



int soucin(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci
    int pro = 1;
    for (int number : cisla) {
        pro *= number;
    }
    return pro;
    //return 0;
}

double prumer(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci
    if (cisla.empty()) return 0;
    double sum = soucet(cisla);
    return sum / cisla.size();
    //return 0;
}

double median(const std::vector<int> &cisla)
{
    if (cisla.empty()) return 0;

    // Vytvoření kopie a seřazení vstupního vektoru
    std::vector<int> sortedCisla = cisla;
    std::sort(sortedCisla.begin(), sortedCisla.end());
    
    int pocetPrvku = sortedCisla.size();
    int middle = pocetPrvku / 2;

    if (pocetPrvku % 2 == 0) {
        // Medián pro sudý počet prvků - průměr dvou prostředních hodnot
        return (sortedCisla[middle - 1] + sortedCisla[middle]) / 2.0;
    } else {
        // Medián pro lichý počet prvků - prostřední hodnota
        return sortedCisla[middle];
    }

    /*
    int middle = cisla.size() / 2;
    double median;
    if (cisla.size() % 2 == 0) {
        median = (cisla[middle - 1] + cisla[middle]) / 2.0;
    } else {
        median = cisla[middle];
    }
    return median;
    */
    
    // TODO: Implementujte funkci
    //return 0;
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

/*
cd Ukol_3/cpp
make build
cd build 

cmake ..
make
./mytests
*/
