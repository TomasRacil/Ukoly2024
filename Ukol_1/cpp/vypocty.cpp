// #include "vypocty.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int soucet(const std::vector<int> &cisla)
{
    int sum = 0;
    for (int i = 0; i<cisla.size(); i++){
        sum+= i;
    }
    return sum;
}

int soucin(const std::vector<int> &cisla)
{
    int sum = 1;
    for (int i = 1; i<cisla.size(); i++){
        sum*= i;
    }
        return sum;
}

double prumer(const std::vector<int> &cisla)
{
    return soucet(cisla)/cisla.size();
}

double median(const std::vector<int> &cisla)
{
       double median;
   sort(cisla.begin(), cisla.end());
   if (cisla.size() % 2 == 0) { //podminka pro sude cisla
       median = (cisla[cisla.size() / 2 - 1] + cisla[cisla.size() / 2]) / 2.0;
   }
   else {
       median = cisla[cisla.size() / 2]; //staci pouze prostredni hodnota
   }
return median;
    
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    // TODO: Načtěte čísla ze vstupu do vektoru cisla

    for(int i = 0; i<vstup.size(); i++){
        if(isdigit(vstup[i])){
            cisla.push_back(vstup[i] - '0');
        }
    }
    

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__
