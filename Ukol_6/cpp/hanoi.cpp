#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // clen pro ulozeni stavu vezi po provedeni tahu
};

// Funkce pro provedeni tahu
void provedTah(vector<vector<int>>& veze, Tah& tah) {
    if (veze[tah.z - 'A'].empty()) {
        throw runtime_error("Chyba: Vez " + string(1, tah.z) + " je prazdna, nelze provest tah.");
    }

    // Odebrani disku z veze 'z'
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();

    // Pridani disku na vez 'na'
    veze[tah.na - 'A'].push_back(disk);

    // Ulozeni stavu vezi do tahu
    tah.disk = disk;
    tah.stavVezi = veze;
}

// Funkce pro reseni Hanojskych vezi (bez vypisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy) {
    if (n <= 0) {
        return; // Nic nedelame pro nulovy nebo zaporny pocet disku
    }
    if (veze[0].empty() && veze[1].empty() && veze[2].empty()) {
        for (int i = n; i > 0; i--) {
            veze[0].push_back(i);
        }
    }

    if (n == 1) {
        // Zakladni pripad: Presun jednoho disku
        Tah tah = { 0, z, cil, {} };
        provedTah(veze, tah);
        tahy.push_back(tah);
    }
    else {
        // Rekurzivni rozdeleni problemu
        hanoi(n - 1, z, cil, pomocny, veze, tahy); // Presun n-1 disku na pomocnou vez
        Tah tah = { 0, z, cil, {} };
        provedTah(veze, tah); // Presun nejvetsiho disku na cilovou vez
        tahy.push_back(tah);
        hanoi(n - 1, pomocny, z, cil, veze, tahy); // Presun n-1 disku na cilovou vez
    }
}

// Funkce pro zobrazeni vezi v konzoli
void zobrazVeze(const vector<vector<int>>& veze) {
    if (veze.empty()) {
        cout << "Zadne veze k zobrazeni." << endl;
        return;
    }

    int maxHeight = 0;
    for (const auto& vez : veze) {
        maxHeight = max(maxHeight, static_cast<int>(vez.size()));
    }

    for (int i = maxHeight - 1; i >= 0; --i) {
        for (const auto& vez : veze) {
            if (i < vez.size()) {
                cout << setw(5) << vez[i];
            }
            else {
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
    }

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro ulozeni tahu
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazeni tahu a stavu vezi
    for (const Tah& tah : tahy) {
        cout << "Presun disk " << tah.disk << " z koliku " << tah.z << " na kolik " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazeni stavu vezi po tahu
    }

    return 0;
}
#endif // __TEST__