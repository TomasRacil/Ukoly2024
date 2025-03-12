#include <iostream>
#include <vector>

using namespace std;

// Struktura pro zobrazení tahu
struct Tah
{
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; //uloží stav veží po táhnutí
};

// Funkce pro provedení tahu (mění stav věží a aktualizuje tah)
void provedTah(vector<vector<int>> &veze, Tah &tah)
{
    // Přesunutí disku mezi dvěma kolíky
    if(!veze[tah.z-'A'].empty()){
        veze[tah.na - 'A'].push_back(tah.disk);
        veze[tah.z - 'A'].pop_back();
    }
    // Uložení stavu věží po tahu
    tah.stavVezi = veze;
}

//pro řešení Hanojských věží 
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    if (n<=0) return;

     if (veze[z - 'A'].empty()) {
        for (int i = n; i > 0; i--) {
            veze[z - 'A'].push_back(i);
        }
     }
    
    if(n==1)
    {
        //přesunutí jednoho disku
       // if (veze[z - 'A'].empty()) return;
        Tah tah;
        tah.disk = veze[z - 'A'].back();
        tah.z = z;
        tah.na = cil;
        provedTah(veze, tah); // Provede tah a uloží nový stav věží
        tahy.push_back(tah);
        return;
    }

    //přesunutí n-1 disků na pomocný kolík
    hanoi(n - 1, z, cil, pomocny, veze, tahy);
    if (veze[z - 'A'].empty()) return;
    

    //přesunutí posledního disku na cílový kolík
    Tah tah;
   
    tah.disk = veze[z - 'A'].back();
    tah.z = z;
    tah.na = cil;
    provedTah(veze, tah);
    tahy.push_back(tah);

    //přesunutí n-1 disků z pomocného kolíku na cílový kolík
    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

//zobrazení věží
void zobrazVeze(const vector<vector<int>> &veze)
{
    // Zobrazení každé věže
    for (int i = 0; i < 3; i++)
    {
        cout << "Kolík " << char('A' + i) << ": ";
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

    if (n <= 0)
    {
        cout << "Počet disků musí být větší než 0!" << endl;
        return 1;
    }

    // Inicializace věží (první věž obsahuje všechny disky)
    vector<vector<int>> veze(3);
    vector<Tah> tahy; // Vektor pro uložení tahů

    tahy.clear();
    
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i);
    }
    
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (const Tah &tah : tahy)
    {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
