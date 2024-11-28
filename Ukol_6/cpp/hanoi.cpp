#include <iostream>
#include <vector>

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
void provedTah(vector<vector<int>>& veze, Tah tah)
{
    int start = tah.z - 'A';
    int cil = tah.na - 'A';

    if (veze[start].empty())
    {
        return;
    }

    
    tah.disk = veze[start].back();
    veze[start].pop_back();
    veze[cil].push_back(tah.disk);
    

}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy)
{
    if (n <= 0)
    {
        return;       
    }

    if (n == 1)
    {
        Tah tah = { n,z,cil,veze };
        provedTah(veze, tah);
        tah.stavVezi = veze;
        tahy.push_back(tah);
        return;
    }

    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    Tah tah = { n,z,cil,veze };
    provedTah(veze, tah);
    tah.stavVezi = veze;
    tahy.push_back(tah);

    hanoi(n - 1, pomocny, z, cil, veze, tahy);



}

void zobrazVeze(vector<vector<int>>& veze)
{
    for (size_t i = 0; i < veze.size(); i++)
    {
        cout << "Kolik " << char('A' + i) << ": ";
        for (int disk : veze[i])
        {
            cout << disk << " ";
        }
        cout << endl;
    }

    cout << "------------------" << endl;
}

#ifndef __TEST__
int main()
{
    int n;
    cout << "Zadejte pocet disku: ";
    cin >> n;
    cin.ignore();

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
        cout << "Presun disk " << tah.disk << " z koliku " << tah.z << " na kolik " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__