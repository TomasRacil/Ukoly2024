#include <iostream>
#include <vector>

int soucet(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci
    return 0;
}

int soucin(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci
    return 0;
}

double prumer(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci
    return 0;
}

double median(const std::vector<int> &cisla)
{
    // TODO: Implementujte funkci
    return 0;
}

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