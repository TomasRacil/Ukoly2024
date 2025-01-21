#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept> // For exceptions

int soucet(const std::vector<int>& cisla)
{
    int sum = 0;
    for (int num : cisla)
    {
        sum += num;
    }
    return sum;
}

int soucin(const std::vector<int>& cisla)
{
    if (cisla.empty())
    {
        return 0; // Return 0 for an empty list
    }

    int product = 1;
    for (int num : cisla)
    {
        product *= num;
    }
    return product;
}

double prumer(const std::vector<int>& cisla)
{
    if (cisla.empty())
    {
        throw std::invalid_argument("Cannot calculate the average of an empty list");
    }

    int sum = soucet(cisla);
    return static_cast<double>(sum) / cisla.size();
}

double median(std::vector<int> cisla)
{
    if (cisla.empty())
    {
        throw std::invalid_argument("Cannot calculate the median of an empty list");
    }

    std::sort(cisla.begin(), cisla.end());
    int n = cisla.size();

    if (n % 2 == 0)
    {
        return (cisla[n / 2 - 1] + cisla[n / 2]) / 2.0;
    }
    else
    {
        return cisla[n / 2];
    }
}

int main()
{
    try
    {
        std::cout << "Zadejte seznam cisel oddlenych carkou: ";
        std::string vstup;
        std::getline(std::cin, vstup);

        std::vector<int> cisla;
        std::stringstream ss(vstup);
        std::string hodnota;

        while (std::getline(ss, hodnota, ','))
        {
            if (!hodnota.empty())
            {
                cisla.push_back(std::stoi(hodnota));
            }
        }

        std::cout << "Soucet: " << soucet(cisla) << std::endl;
        std::cout << "Soucin: " << soucin(cisla) << std::endl;

        try
        {
            std::cout << "Prumerna hodnota: " << prumer(cisla) << std::endl;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }

        try
        {
            std::cout << "Median: " << median(cisla) << std::endl;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Chyba pri zpracovani vstupu: " << e.what() << std::endl;
    }

    return 0;
}
