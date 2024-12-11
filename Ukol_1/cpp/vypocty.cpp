
// #include "vypocty.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;



int soucet(const std::vector<int> &cisla)
{
    if (cisla.empty()) {
        return 0; // Return 0 if the vector is empty
    }
    int soucet = 0;
    for (int i = 0; i < cisla.size(); i++)
    {
        soucet = soucet + cisla[i];
    }
    return soucet;
}

int soucin(const std::vector<int> &cisla)
{
    if (cisla.empty()) {
        return 1; // Return 1 if the vector is empty (neutral element for multiplication)
    }
    int soucin = 1;
    for (int i = 0; i < cisla.size(); i++)
    {
        soucin = soucin * cisla[i];
    }
    return soucin;
}

double prumer(const std::vector<int> &cisla)
{
    if (cisla.empty()) {
        throw exception(); // Throw an exception if the vector is empty
    }
    int prumerr = 0;
    for (int i = 0; i < cisla.size(); i++)
    {
        prumerr = prumerr + cisla[i];
    }
    return static_cast<double>(prumerr) / cisla.size();
}

double median(std::vector<int> &cisla)
{
    if (cisla.empty()) {
        throw exception(); // Throw an exception if the vector is empty
    }
    sort(cisla.begin(), cisla.end());
    int pocet = cisla.size();
    double median = 0.0;
    if (pocet % 2 != 0)
    {
        median = cisla[pocet / 2];
    }
    else
    {
        median = (cisla[pocet / 2] + cisla[pocet / 2 - 1]) / 2.0;
    }
    return median;
}

//#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::stringstream ss(vstup);
    std::string token;

    // Parse the input string and convert to integers
    while (std::getline(ss, token, ','))
    {
        try
        {
            int number = std::stoi(token);
            cisla.push_back(number);
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Invalid input: " << token << std::endl;
            return -1;
        }
    }


    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
//#endif // __TEST__
