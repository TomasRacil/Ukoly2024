#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

int soucet(std::vector<int> cisla)
{
    int suma= 0;
    for (int i =0; i < cisla.size(); i++) {
        suma += cisla[i];
    }
    return suma;
}

int soucin(std::vector<int> cisla)
{
    int soucin= 1;
    for (int i = 0; i < cisla.size(); i++) {
        soucin *= cisla[i];
    }
    return soucin;
}

double prumer(const std::vector<int> &cisla)
{
    if (cisla.empty()) return 0;
    double suma =soucet(cisla);
    return suma / cisla.size();
}

double median (const std::vector<int> &cisla)
{
    if (cisla.empty()) return 0;
    std::vector<int> kopie= cisla;
    std::sort(kopie.begin(), kopie.end());

    int n= kopie.size();
    if (n % 2==0) {
        return (kopie[n /2-1]+ kopie [n / 2]) / 2.0;
    } else {
        return kopie[n/2];
    }
}

int main()
{
    std::cout << "zadej cisla oddelena carkama: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::string cislo;

    for (int i = 0; i < vstup.length(); i++) {
        if (vstup[i] != ',') {
            cislo += vstup[i];
        } else {
            if (cislo != "") {
                cisla.push_back(std::stoi(cislo));
                cislo = "";
            }
        }
    }

    if (cislo != "") {
        cisla.push_back(std::stoi(cislo));
    }


    std::cout << "soucet : " << soucet(cisla) << std::endl;
    std::cout << "soucin: " << soucin(cisla) << std::endl;
    std::cout << "prumerna hodnota: " << prumer(cisla) << std::endl;
    std::cout << "median: " << median(cisla) << std::endl;

    return 0;
}
