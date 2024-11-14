// #include "vypocty.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

int soucet(const std::vector<int> &cisla)
{
    int sum = 0;
    for (auto i : cisla) {
        sum += i;
    }
    return sum;
}

int soucin(const std::vector<int> &cisla)
{
    int sum = 1;
    for (auto i : cisla) {
        sum *= i;
    }
    return sum;
}

double prumer(const std::vector<int> &cisla)
{
    return soucet(cisla)/cisla.size();
}

double median(std::vector<int> &cisla)
{
    std::sort(cisla.begin(), cisla.end());
    if (cisla.size()%2){
        return cisla[cisla.size()/2];
    }
    return (cisla[cisla.size()/2] + cisla[cisla.size()/2 - 1])/(double)2;
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::stringstream ss(vstup);
    while(ss.good()) {
        std::string substr;
        std::getline(ss, substr, ',');
        cisla.push_back(std::stoi(substr));
    }

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__
