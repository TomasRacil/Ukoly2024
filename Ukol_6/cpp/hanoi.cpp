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
void provedTah(vector<vector<int>> &veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);
}

// Funkce pro zobrazeni vezi v konzoli
void zobrazVeze(const vector<vector<int>> &veze, int maxDisks) {
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
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, int maxDisks) {
    if (n == 0) return;

    // Přesun n-1 disků na pomocný kolík
    hanoi(n - 1, z, cil, pomocny, veze, maxDisks);

    // Informace o aktuálním tahu
    cout << "Presun disk " << n << " z koliku " << z << " na kolik " << cil << endl;

    // Aktualizace stavu věží po tahu
    Tah tah;
    tah.disk = n;
    tah.z = z;
    tah.na = cil;
    provedTah(veze, tah);

    // Vizualizace aktuálního stavu
    zobrazVeze(veze, maxDisks);

    // Přesun n-1 disků z pomocného kolíku na cílový
    hanoi(n - 1, pomocny, z, cil, veze, maxDisks);
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

    // Vizualizace počátečního stavu
    zobrazVeze(veze, n);

    // Řešení Hanojských věží
    hanoi(n, 'A', 'B', 'C', veze, n);

    return 0;
}
#endif
