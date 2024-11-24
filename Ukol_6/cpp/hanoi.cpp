#include <iostream>
#include <vector>
#include <iomanip> // Pro zarovnání výstupu

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah
{
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah)
{
    // Odebereme disk z počáteční věže
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();

    // Přidáme disk na cílovou věž
    veze[tah.na - 'A'].push_back(disk);

    // Uložíme aktuální stav věží do tahu
    tah.stavVezi = veze;
}

// Funkce pro vizualizaci věží
void zobrazVeze(vector<vector<int>> &veze)
{
    int maxHeight = 0;
    for (const auto &vez : veze)
    {
        maxHeight = max(maxHeight, (int)vez.size());
    }

    for (int i = maxHeight - 1; i >= 0; --i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (i < veze[j].size())
            {
                cout << setw(5) << veze[j][i] << setw(5);
            }
            else
            {
                cout << setw(5) << "|" << setw(5);
            }
        }
        cout << endl;
    }
    cout << "   A           B           C   " << endl << endl;
}

// Funkce pro řešení Hanoiských věží
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    if (n <= 0)
    {
        return; // Nic neprovádíme, pokud je počet disků menší nebo roven nule
    }
    if (n == 1)
    {
        Tah tah = {n, z, cil, veze};
        provedTah(veze, tah);
        tahy.push_back(tah);
    }
    else
    {
        hanoi(n - 1, z, cil, pomocny, veze, tahy);

        Tah tah = {n, z, cil, veze};
        provedTah(veze, tah);
        tahy.push_back(tah);

        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

#ifndef __TEST__
int main()
{
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    if (n <= 0)
    {
        cout << "Počet disků musí být větší než 0!" << endl;
        return 1;
    }

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (Tah tah : tahy)
    {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
