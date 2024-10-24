#include <iostream>
#include <vector>
#include <sstream>

int soucet(const std::vector<int> &cisla)
{
    int sct = 0;
    for (int i : cisla) {
        sct += i;
    }
    return sct;
}

int soucin(const std::vector<int> &cisla)
{
    int sc = 1;
    for (int i : cisla) {
        sc *= i;
    }
    return sc;
}

double prumer(const std::vector<int> &cisla)
{
    double avg = 0;
    for (int i : cisla) {
        avg += i;
    }
    avg = avg / cisla.size();
    return avg;
}

double median(const std::vector<int> &cisla)
{
    double med = 0;
    if (cisla.size() % 2 == 0) {
        med = (cisla[cisla.size() / 2 - 1] + cisla[cisla.size() / 2]) / 2;
    } else {
        med = cisla[cisla.size() / 2];
    }
    return med;
}

int main()
{
    std::cout << "Zadejte seznam cisel oddelených carkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);
    std::vector<int> cisla;
    std::stringstream ss(vstup);
    std::string temp;
    while (std::getline(ss, temp, ',')) {
        cisla.push_back(std::stoi(temp));
    }
    
     if(cisla.size() == 0){
        std::cout << "Nezadal jste zadne cislo." << std::endl;
        return 1;
    }

    std::cout << "Soucet: " << soucet(cisla) << std::endl;
    std::cout << "Soucin: " << soucin(cisla) << std::endl;
    std::cout << "Prumerna hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Median: " << median(cisla) << std::endl;

    return 0;
}
