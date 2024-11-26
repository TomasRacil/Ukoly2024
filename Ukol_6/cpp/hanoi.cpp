#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, char z, char na) {
    int disk = veze[z - 'A'].back();
    veze[z - 'A'].pop_back();
    veze[na - 'A'].push_back(disk);
}

// Funkce pro zobrazení věží v konzoli
void zobrazVeze(const vector<vector<int>> &veze) {
    int maxDisks = 0;
    for (const auto &vezeKolik : veze) {
        maxDisks = max(maxDisks, (int)vezeKolik.size());
    }

    for (int i = maxDisks - 1; i >= 0; --i) {
        for (int j = 0; j < 3; ++j) {
            if (i < veze[j].size()) {
                cout << setw(3) << veze[j][i];
            } else {
                cout << setw(3) << "|";
            }
            cout << "   ";
        }
        cout << endl;
    }
    // Označení kolíků
    cout << "  A      B      C  " << endl;
    cout << endl;
}

// Funkce pro řešení Hanojských věží
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n <= 0) return; // Pokud je počet disků neplatný, ukončete funkci

    // Přesun n-1 disků na pomocný kolík
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    // Uložení aktuálního tahu
    Tah tah;
    tah.disk = n;
    tah.z = z;
    tah.na = cil;

    // Aktualizace stavu věží před uložením
    provedTah(veze, z, cil);

    // Uložit aktuální stav věží
    tah.stavVezi = veze;
    tahy.push_back(tah);

    // Vizualizace aktuálního stavu
    cout << "Presun disk " << n << " z koliku " << z << " na kolik " << cil << endl;
    zobrazVeze(veze);

    // Přesun n-1 disků z pomocného kolíku na cílový
    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte pocet disku: ";
    cin >> n;

    if (n <= 0) {
        cout << "Pocet disku musi byt vetsi nez nula." << endl;
        return 1;
    }

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; --i) {
        veze[0].push_back(i); // Naplnění kolíku A
    }

    vector<Tah> tahy; // Vektor pro ukládání tahů

    // Vizualizace počátečního stavu
    zobrazVeze(veze);

    // Řešení Hanojských věží
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    return 0;
}
#endif
