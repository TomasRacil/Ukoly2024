#include <iostream>
#include <vector>
#include <iomanip>

/*
Pro každý disk je potřeba provést určité množství tahů, které se zvyšují exponenciálně:
Pro 1 disk je potřeba 1 tah.
Pro 2 disky jsou potřeba 3 tahy.
Pro 3 disky jsou potřeba 7 tahů.
Pro 4 disky jsou potřeba 15 tahů.
Pro 5 disků 31 tahů, a tak dále.
*/
using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah &tah) {
    // Odebrání disku z věže 'z'
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();

    // Přidání disku na věž 'na'
    veze[tah.na - 'A'].push_back(disk);

    // Uložení stavu věží do tahu
    tah.stavVezi = veze;
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n <= 0) return; // Neplatné množství disků

    if (n == 1) {
        // Základní případ: Přesun jednoho disku
        Tah tah = {veze[z - 'A'].back(), z, cil};
        provedTah(veze, tah);
        tahy.push_back(tah);
    } else {
        // Rekurzivní rozdělení problému
        hanoi(n - 1, z, cil, pomocny, veze, tahy); // Přesun n-1 disků na pomocnou věž
        Tah tah = {veze[z - 'A'].back(), z, cil};
        provedTah(veze, tah); // Přesun největšího disku na cílovou věž
        tahy.push_back(tah);
        hanoi(n - 1, pomocny, z, cil, veze, tahy); // Přesun n-1 disků na cílovou věž
    }
}

// Funkce pro zobrazení věží v konzoli
void zobrazVeze(const vector<vector<int>> &veze) {
    int maxHeight = 0;
    for (const auto &vez : veze) {
        maxHeight = max(maxHeight, static_cast<int>(vez.size()));
    }

    for (int i = maxHeight - 1; i >= 0; --i) {
        for (const auto &vez : veze) {
            if (i < vez.size()) {
                cout << setw(5) << vez[i];
            } else {
                cout << setw(5) << "|";
            }
        }
        cout << endl;
    }

    cout << "  A    B    C  " << endl;
    cout << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte pocet disku: ";
    cin >> n;

    if (n <= 0) {
        cout << "Pocet disku musi byt kladne cislo." << endl;
        return 1;
    }

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (const Tah &tah : tahy) {
        cout << "Presun disk " << tah.disk << " z koliku " << tah.z << " na kolik " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
