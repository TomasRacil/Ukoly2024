#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

// Function to calculate the sum of elements in a vector
int soucet(const std::vector<int> &cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 0);
}

// Function to calculate the product of elements in a vector
int soucin(const std::vector<int> &cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 1, std::multiplies<int>());
}

// Function to calculate the average of elements in a vector
double prumer(const std::vector<int> &cisla)
{
    if (cisla.empty()) return 0.0;
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

// Function to calculate the median of elements in a vector
double median(std::vector<int> cisla)
{
    if (cisla.empty()) return 0.0;
    
    std::sort(cisla.begin(), cisla.end());
    size_t size = cisla.size();
    
    if (size % 2 == 0)
        return (cisla[size / 2 - 1] + cisla[size / 2]) / 2.0;
    else
        return cisla[size / 2];
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::stringstream ss(vstup);
    std::string item;

    // Parse the input string and store each number in the vector
    while (std::getline(ss, item, ','))
    {
        cisla.push_back(std::stoi(item));
    }

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__
