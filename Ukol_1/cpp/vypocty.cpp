#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
using namespace std;


int soucet(const std::vector<int>& cisla) {
    return std::accumulate(cisla.begin(), cisla.end(), 0);
}

int soucin(const std::vector<int>& cisla) {
    int soucin = 1;
    for (int cislo : cisla) {
        soucin *= cislo;
    }
    return soucin;
}

double prumer(const std::vector<int>& cisla) {
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

double median(std::vector<int> cisla) {
    std::sort(cisla.begin(), cisla.end());
    int n = cisla.size();
    if (n % 2 == 0) {
        return (cisla[n / 2 - 1] + cisla[n / 2]) / 2.0;
    }
    else {
        return cisla[n / 2];
    }
}

#ifndef TEST
int main() {
    cout << "Zadejte seznam čísel oddělených čárkou: ";
    string vstup;
    getline(cin, vstup);

    vector<int> cisla;
    stringstream ss(vstup);
    string temp;
    while (getline(ss, temp, ',')) {
        cisla.push_back(stoi(temp));
    }

    cout << "Součet: " << soucet(cisla) << endl;
    cout << "Součin: " << soucin(cisla) << endl;
    cout << "Průměrná hodnota: " << prumer(cisla) << endl;
    cout << "Medián: " << median(cisla) << endl;

    return 0;
}
#endif