#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah
{
    int disk;
    char z; // start
    char na; // cil
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah)
{
    int start = tah.z - 'A';
    int cil = tah.na - 'A';

    int disk = veze[start].back(); // Vezmu vrchoni disk
    veze[start].pop_back();        // Odstranim vrchni disk
    veze[cil].push_back(disk);  // Pridam disk na cilovou vez
    
    tah.stavVezi = veze; // ulozim
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    if (n == 0) return; // nema smysl pro nula disku
    else if (n == 1){
        // presunu primo do cile
        Tah tah;
        tah.disk = veze[z - 'A'].back(); // disk na presun
        tah.z = z;
        tah.na = cil;
        provedTah(veze, tah);
        tah.stavVezi = veze; // ulozim
        tahy.push_back(tah);
    }
    else{
        // presunuti n-1 disku na pomocny, prostredni kolik
        hanoi(n - 1, z, cil, pomocny, veze, tahy);
        
        // presunu nejvetsi disk na cilovy kolik
        Tah tah;
        tah.disk = veze[z - 'A'].back();
        tah.z = z;
        tah.na = cil;
        provedTah(veze, tah);
        tah.stavVezi = veze;
        tahy.push_back(tah);
        
        // presunu n-1 disku na cilovy kolik
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

void zobrazVeze(vector<vector<int>> &veze)
{
    int maxVyska = 0;
    for (const auto &vez : veze){
        if (vez.size() > maxVyska)
            maxVyska = vez.size();
    }

    for (int i = maxVyska - 1; i >= 0; i--){
        for (const auto &vez : veze){
            if (i < vez.size()){
                cout << " " << vez[i] << " ";
            }
            else{
                cout << " | ";
            }
        }
        cout << endl;
    }
    cout << "--- --- ---" << endl;
    cout << " A   B   C " << endl;
}

#ifndef __TEST__
int main()
{
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    zobrazVeze(veze);
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
