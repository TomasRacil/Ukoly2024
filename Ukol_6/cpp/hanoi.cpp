#include <iostream>
#include <vector>
#include <stdexcept>

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
    // Najdeme indexy věží
    int zIndex = tah.z - 'A';
    int naIndex = tah.na - 'A';

    // Přesuneme disk z věže zIndex na věž naIndex
    if (!veze[zIndex].empty()) {
        int disk = veze[zIndex].back();
        veze[zIndex].pop_back();
        veze[naIndex].push_back(disk);

        // Aktualizujeme stav věží v tahu
        tah.stavVezi = veze;
    }
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n <= 0) {
        return; // řešení vstupu uživatele pokud zadá špatně číslo
    }
    if (n == 1) {
        // Provedeme tah a uložíme ho
        Tah tah = {n, z, cil, veze};
        provedTah(veze, tah);
        tahy.push_back(tah);
    } else {
        // Přesuneme n-1 disků na pomocný kolík
        hanoi(n - 1, z, cil, pomocny, veze, tahy);
        // Přesuneme největší disk na cílový kolík
        Tah tah = {n, z, cil, veze};
        provedTah(veze, tah);
        tahy.push_back(tah);
        // Přesuneme n-1 disků z pomocného kolíku na cílový kolík
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

void zobrazVeze(const vector<vector<int>> &veze) {
    for (int i = 0; i < 3; ++i) {
        cout << "Věž " << char('A' + i) << ": ";
        for (int disk : veze[i]) {
            cout << disk << " ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (const Tah &tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__