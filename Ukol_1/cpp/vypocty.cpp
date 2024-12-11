#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int soucet(const vector<int>& cisla)
{
<<<<<<< HEAD
    // TODO: Implementujte funkci
    return 0;
=======
>>>>>>> a465025ba0496aef51e9e896e65c4174956c099e
    int sum = 0;
    for (int num : cisla) {
        sum += num;
    }
    return sum;
}

int soucin(const vector<int>& cisla)
{
<<<<<<< HEAD
    // TODO: Implementujte funkci
    return 0;
=======
>>>>>>> a465025ba0496aef51e9e896e65c4174956c099e
    int product = 1;
    for (int num : cisla) {
        product *= num;
    }
    return product;
}

double prumer(const vector<int>& cisla)
{
<<<<<<< HEAD
    // TODO: Implementujte funkci
    return 0;
    if (cisla.empty()) return 0;
    return static_cast<double>(soucet(cisla)) / cisla.size();
=======
    if (cisla.empty()) return 0;
    return staticcast<double>(soucet(cisla)) / cisla.size();
>>>>>>> a465025ba0496aef51e9e896e65c4174956c099e
}

double median(const vector<int>& cisla)
{
<<<<<<< HEAD
    // TODO: Implementujte funkci
    if (cisla.empty()) return 0;
    vector<int> sorted = cisla;
    sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    if (size % 2 == 0) {
        return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    }
    else {
=======
    if (cisla.empty()) return 0;
    vector<int> sorted = cisla;
    sort(sorted.begin(), sorted.end());
    sizet size = sorted.size();
    if (size % 2 == 0) {
        return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    } else {
>>>>>>> a465025ba0496aef51e9e896e65c4174956c099e
        return sorted[size / 2];
    }
}

#ifndef TEST // Add this preprocessor guard
int main()
{
    cout << "Zadejte seznam čísel oddělených čárkou: ";
    string vstup;
    getline(cin, vstup);

<<<<<<< HEAD
    // TODO: Načtěte čísla ze vstupu do vektoru cisla
=======
>>>>>>> a465025ba0496aef51e9e896e65c4174956c099e
    vector<int> cisla;
    stringstream ss(vstup);
    string temp;
    while (getline(ss, temp, ',')) {
        cisla.push_back(stoi(temp));
    }

<<<<<<< HEAD
    
=======
>>>>>>> a465025ba0496aef51e9e896e65c4174956c099e
    cout << "Součet: " << soucet(cisla) << endl;
    cout << "Součin: " << soucin(cisla) << endl;
    cout << "Průměrná hodnota: " << prumer(cisla) << endl;
    cout << "Medián: " << median(cisla) << endl;

    return 0;
}
<<<<<<< HEAD
#endif // __TEST__
=======
#endif // __TEST
>>>>>>> a465025ba0496aef51e9e896e65c4174956c099e
