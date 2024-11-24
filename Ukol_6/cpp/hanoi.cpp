#include <iostream>
#include <vector>

using namespace std;
// hanoi towers recurisve function

// Struktura pro reprezentaci tahu
struct Tah
{
    int disk; // Číslo disku
    char z; // Zdrojová věž
    char na; // Cílová věž
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah)
{
    int disk = tah.disk; // Uložení disku
    char z = tah.z; // Uložení zdrojové veže
    char na = tah.na; // Uložení cílové veže
    veze[z - 'A'].pop_back(); // Odeber disk ze zdrojove veze
    veze[na - 'A'].push_back(disk); // Přidej disk na cílovou vez
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    if (n == 1)
    {
        Tah tah;
        tah.disk = n; // Disk ktery se presouva
        tah.z = z; // Zdrojova vez
        tah.na = cil; // Cilova vez
        tah.stavVezi = veze; // Stav vezi
        provedTah(veze, tah); // Proved tah
        tahy.push_back(tah); // Přidej tah do vektoru tahů
    }
    else
    {
        hanoi(n - 1, z, cil, pomocny, veze, tahy);
        Tah tah;
        tah.disk = n; //
        tah.z = z;
        tah.na = cil;
        tah.stavVezi = veze;
        provedTah(veze, tah); //
        tahy.push_back(tah); // Přidej tah do vektoru tahů
        hanoi(n - 1, pomocny, z, cil, veze, tahy); // Rekurzivní volání pro přesun disku
    }

}

void zobrazVeze(vector<vector<int>> &veze)
{
    //show towers
    for (int i = 0; i < veze.size(); i++) // Ukaz veze
    {
        cout << "Vez " << char('A' + i) << ": ";
        for (int j = 0; j < veze[i].size(); j++) // Ukaz disky na vezi
        {
            cout << veze[i][j] << " ";
        }
        cout << endl;
    }
}

#ifndef __TEST__
int main()
{
    int n; // Pocet disku
    cout << "Zadejte pocet disku: ";
    cin >> n;
    cin.ignore();
    if (n < 1)
    {
        cout << "Pocet disku musi byt kladne cislo" << endl;
        return 1;
    }
    if (cin.fail()){
        cout << "Nespravny vstup." << endl;
        return 1;
    }
    if (n == 0)
    {
        cout << "Prazdny vstup." << endl;
        return 1;
    }

    vector<vector<int>> veze(3); // Vektor pro uložení stavu věží
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i); //Pridej disky na prvni vez
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy); // vyres hanoi

    // Zobrazení tahů a stavů věží
    int tahCount = 1; // Pocitadlo tahu
    for (Tah tah : tahy)
    {
        cout << "Tah" << tahCount << endl; // tah cislo:
        cout << "Presun disk " << tah.disk << " z koliku " << tah.z << " na kolik " << tah.na << endl;
        tahCount++;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__