#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

int soucet(const std::vector<int> &cisla)
{
    int sum = 0;
    for(int i = 0; i<cisla.size(); i++){
        sum = sum + cisla[i];
    }
    return sum;
}

int soucin(const std::vector<int> &cisla)
{
    int dotProduct = 1;
    for(int i = 0; i<cisla.size(); i++){
        dotProduct = dotProduct * cisla[i];
    }
    return dotProduct;
}

double prumer(const std::vector<int> &cisla)
{
    double units = 0;
    double sum = 0;
    for(int i = 0; i<cisla.size(); i++){
        units++;
        sum = sum + double(cisla[i]);
    }

    return sum/units;
}

double median(const std::vector<int> &cisla)
{
    std::vector<int> sortedCisla = cisla;
    std::sort(sortedCisla.begin(), sortedCisla.end());

    size_t n = sortedCisla.size();
    if (n % 2 == 0)
    {
        return (sortedCisla[n / 2 - 1] + sortedCisla[n / 2]) / 2.0;
    }
    else
    {
        return sortedCisla[n / 2];
    }
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{

    std::cout << "Zadejte seznam čísel oddělených čárkou: \n";
    std::string vstup;
       std::vector<int> cisla;

    try{
        std::getline(cin, vstup);

        std::stringstream stringStream(vstup);
        std::string temp;
        while (getline(stringStream, temp, ',')) {
            cisla.push_back(stoi(temp));
        }
    }catch(const invalid_argument& e) {
        std::cout << " :( \n";
        }


    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}
#endif // __TEST__
