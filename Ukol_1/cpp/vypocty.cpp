#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

int soucet(const std::vector<int> &cisla)
{
    if (cisla.empty()) {
        return 0; // Return 0 if the vector is empty
    }
    int soucet = 0;
    for (int i = 0; i < cisla.size(); i++)
    {
        soucet = soucet + cisla[i];
    }
    return soucet;
}

int soucin(const std::vector<int> &cisla)
{
    if (cisla.empty()) {
        return 1; // Return 1 if the vector is empty (neutral element for multiplication)
    }
    int soucin = 1;
    for (int i = 0; i < cisla.size(); i++)
    {
        soucin = soucin * cisla[i];
    }
    return soucin;
}

double prumer(const std::vector<int> &cisla)
{
    if (cisla.empty()) {
        return 0.0; // Return 0.0 if the vector is empty
    }
    int prumerr = 0;
    for (int i = 0; i < cisla.size(); i++)
    {
        prumerr = prumerr + cisla[i];
    }
    return static_cast<double>(prumerr) / cisla.size();
}