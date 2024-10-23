
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main()
{
    int num;
    string zero;
    int soucet = 0;
    int nasobeni = 1;
    int pocet = 0;
    double prumer = 0;
    double median = 0;
    cout << "Zadejte čísla: ";
    vector <int> numbers;
    

    while (true)
    {
        num = fgetc(stdin);
        if (num == ',' || num == '\n' || num == EOF)
        {
            int cislo = atoi(zero.c_str());
            soucet += cislo;
            pocet++;
            nasobeni *= cislo;
            numbers.push_back(cislo);
            zero = "";
            if (num =='\n' || num == EOF)
            {
                break;
            }
        }
        else
            zero += num;
    }
        sort(numbers.begin(), numbers.end());

        if (pocet % 2 == 0)
        {
            median = ((double)numbers[pocet / 2] + numbers[pocet / 2 - 1]) / 2;
        }
        else
        {
            median = numbers[pocet / 2];
        }
        prumer = (double)soucet / pocet;

        cout << setprecision(3) << "  Soucet: " << soucet;
        cout << "  Nasobek: " << nasobeni;
        cout << "  Prumer: " << prumer;
        cout << "  Median: " << median;
        
        return 0;
}
