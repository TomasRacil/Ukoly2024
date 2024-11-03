// #include "vypocty.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <sstream>

int soucet(const std::vector<int> &cisla)
{
    int soucet = 0;
    for(int num : cisla)
    {
        soucet += num;
    }
    return soucet;
}

int soucin( std::vector<int> &cisla)
{
    
    int soucin = 1;
    for(int num : cisla)
    {
        soucin *= num;
    }
    return soucin;
}

double prumer(std::vector<int> &cisla)
{
    int n = cisla.size();
    return (n>0)?static_cast<double>(soucet(cisla)) / n : 0;
}

double median(std::vector<int> &cisla)
{
    sort(cisla.begin(), cisla.end());         // seradi cisla podle velikosti
	int n = cisla.size();
    if(n == 0) return 0;
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