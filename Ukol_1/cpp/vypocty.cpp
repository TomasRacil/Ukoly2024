#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void sort_nums(vector<int> &cisla) {
    for (size_t i = 0; i < cisla.size(); i++) {
        for (size_t j = 0; j < cisla.size() - i - 1; j++) {
            if (cisla[j] > cisla[j + 1]) {
                int tmp = cisla[j];
                cisla[j] = cisla[j + 1];
                cisla[j + 1] = tmp;
            }
        }
    }
}

int soucet(const vector<int> &cisla)
{
    int sct = 0;
    for (int i : cisla) {
        sct += i;
    }
    try {
        if (cisla.size() == 0) {
            throw exception();
        }
    } catch (exception) {
        return 0;
    }
    return sct;
}

int soucin(const vector<int> &cisla)
{
    int sc = 1;
    for (int i : cisla) {
        sc *= i;
    }
    try {
        if (cisla.size() == 0) {
            throw exception();
        }
    } catch (exception) {
        return 0;
    }
    return sc;
}

double prumer(const vector<int> &cisla)
{
    try {
        if (cisla.size() == 0) {
            throw exception();
        }
    } catch (exception) {
        cout << "Prazdny vstup." << endl;
        return {};
    }
    double avg = 0;
    for (int i : cisla) {
        avg += i;
    }
    avg = avg / cisla.size();

    return avg;
}

double median(const vector<int> &cisla)
{
    try {
        if (cisla.size() == 0) {
            throw exception();
        }
    } catch (exception) {
        cout << "Prazdny vstup." << endl;
        return {};
    }
    double med = 0;
    vector<int> tmp = cisla;
    sort_nums(tmp);
    if (tmp.size() % 2 == 0) {
        med = (tmp[tmp.size() / 2 - 1] + tmp[tmp.size() / 2]) / 2;
    } else {
        med = tmp[tmp.size() / 2];
    }

    return med;
}

#ifndef __TEST__ 
int main()
{
    cout << "Zadejte seznam cisel oddelených carkou: ";
    string vstup;
    getline(cin, vstup);
    vector<int> cisla;
    stringstream ss(vstup);
    string temp;
    if(vstup.find_first_not_of("0123456789,") != string::npos){
        cout << "Nezadal jste cislo." << endl;
        return 1;
    }
    while (getline(ss, temp, ',')) {
        cisla.push_back(stoi(temp));
    }

    cout << "Soucet: " << soucet(cisla) << endl << "Soucin: " << soucin(cisla) << endl << "Prumer: " << prumer(cisla) << endl << "Median: " << median(cisla) << endl;

    return 0;

}
#endif
