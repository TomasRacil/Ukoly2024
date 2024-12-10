#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int soucet(const vector<int>& cisla)
{
    // TODO: Implementujte funkci
    return 0;
    int sum = 0;
    for (int num : cisla) {
        sum += num;
    }
    return sum;
}

int soucin(const vector<int>& cisla)
{
    // TODO: Implementujte funkci
    return 0;
    int product = 1;
    for (int num : cisla) {
        product *= num;
    }
    return product;
}

double prumer(const vector<int>& cisla)
{
    // TODO: Implementujte funkci
    return 0;
    if (cisla.empty()) return 0;
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

double median(const vector<int>& cisla)
{
    // TODO: Implementujte funkci
    if (cisla.empty()) return 0;
    vector<int> sorted = cisla;
    sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    if (size % 2 == 0) {
        return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    }
    else {
        return sorted[size / 2];
    }
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    cout << "Zadejte seznam čísel oddělených čárkou: ";
    string vstup;
    getline(cin, vstup);

    // TODO: Načtěte čísla ze vstupu do vektoru cisla
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
#endif // __TEST__
