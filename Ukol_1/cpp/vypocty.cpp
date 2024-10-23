#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int soucet(const std::vector<int> &cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 0);
}

int soucin(const std::vector<int> &cisla)
{
    return std::accumulate(cisla.begin(), cisla.end(), 1, std::multiplies<int>());
}

double prumer(const std::vector<int> &cisla)
{
    return soucet(cisla) / cisla.size();
}

double median(const std::vector<int> &cisla)
{
    std::vector<int> tmp = cisla;
    auto m = tmp.begin() + tmp.size() / 2;
    std::nth_element(tmp.begin(), m, tmp.end());
    return tmp.size() & 1
        ? tmp[tmp.size() / 2]
        : ((double) tmp[tmp.size() / 2 - 1] + (double) tmp[tmp.size() / 2]) / 2.0;
}

int main()
{
    std::cout << "Zadejte seznam čísel oddělených čárkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::string buffer;
    auto i = vstup.begin();
    while(i != vstup.end()) {
        while(std::isdigit(*i) and i != vstup.end()) {
            buffer += *(i++);
        }
        if (!buffer.empty()) cisla.push_back(std::stoi(buffer));
        buffer.clear();
        if (i != vstup.end()) ++i;
    }

    std::cout << "Součet: " << soucet(cisla) << std::endl;
    std::cout << "Součin: " << soucin(cisla) << std::endl;
    std::cout << "Průměrná hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Medián: " << median(cisla) << std::endl;

    return 0;
}