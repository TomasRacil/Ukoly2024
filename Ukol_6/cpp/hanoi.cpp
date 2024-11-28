#include <iostream>
#include <vector>

using namespace std;

// Struktura zpbrazení tahu
struct Tah
{
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; //pro uložení stavu věží po provedení tahu
};

//funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah)
{
    // Přesunutí disku mezi dvěma kolíky
    veze[tah.na - 'A'].push_back(tah.disk);
    veze[tah.z - 'A'].pop_back();
    
    // Uložení stavu věží po tahu
    tah.stavVezi = veze;
}

//fnkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    if (n == 1)
    {
        // Přesunutí disku
        Tah tah;
        tah.disk = veze[z - 'A'].back();
        tah.z = z;
        tah.na = cil;
        provedTah(veze, tah);
        tahy.push_back(tah);
        return;
    }

    //volání pro přesunutí n-1 disků na pomocný kolík
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    //presunutí posledního disku na cílový kolík
    Tah tah;
    tah.disk = veze[z - 'A'].back();
    tah.z = z;
    tah.na = cil;
    provedTah(veze, tah);
    tahy.push_back(tah);

    //volání pro přesunutí n-1 disků na cílový kolík
    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

//funkce pro zobrazení věží
void zobrazVeze(vector<vector<int>> &veze)
{
    // Zobrazení každé věže
    for (int i = 0; i < 3; i++)
    {
        cout << "Kolik " << char('A' + i) << ": ";
        for (int disk : veze[i])
        {
            cout << disk << " ";
        }
        cout << endl;
    }
    cout << "---------------------------" << endl;
}

#ifndef __TEST__
int main()
{
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    //inicializace věží (první věž obsahuje všechny disky)
    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    //zobrazení tahů a stavů věží
    for (Tah tah : tahy)
    {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
