#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>  

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
    int product = 1;
    for (int num : cisla)
    {
        product *= num;
    }
    return product;
}

double prumer(const std::vector<int>& cisla)
{
    int sum = soucet(cisla);
    return static_cast<double>(sum) / cisla.size();
}

double median(std::vector<int> cisla)
{
    
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
    std::cout << "Zadejte seznam cisel oddlenych carkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);  

    std::vector<int> cisla;
    std::stringstream ss(vstup);  
    std::string hodnota;
   
    while (std::getline(ss, hodnota, ','))
    {
        cisla.push_back(std::stoi(hodnota));  
    }

    std::cout << "Soucet: " << soucet(cisla) << std::endl;
    std::cout << "Soucin: " << soucin(cisla) << std::endl;
    std::cout << "Prumerna hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Median: " << median(cisla) << std::endl;

    return 0;
}
