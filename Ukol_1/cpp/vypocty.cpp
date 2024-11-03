// #include "vypocty.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

int soucet(const std::vector<int> &cisla)
{
    int n = cisla.size();
    int soucet = 0;
    for(int i=0;i<n;i++)
    {
        soucet += cisla[i];
    }
    return soucet;
}

int soucin(const std::vector<int> &cisla)
{
    
    int n = cisla.size();
    int soucin = 1;
    for(int i=0;i<n;i++)
    {
        soucin *= cisla[i];
    }
    return soucin;
}

double prumer(const std::vector<int> &cisla)
{
    int n = cisla.size();
    double prumer;
    prumer = soucet(cisla)/n;
    return prumer;
}

double median(const std::vector<int> &cisla)
{
    sort(cisla.begin(), cisla.end());         // seradi cisla podle velikosti
	int n = cisla.size();
	if (n % 2 != 0)
	{
		return cisla[n / 2];
	}

	else
		return (cisla[n / 2 - 1] + cisla[n / 2]) / 2.0;
    
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