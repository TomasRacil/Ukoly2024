#include <iostream>
#include <vector>
#include <iomanip> // Pro formátování výpisu věží
#include <cmath>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Uchovává kopii stavu věží
};

// Funkce pro aktualizaci stavu věží po tahu
void provedTah(vector<vector<int>> &veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back();  // Odeber disk z počátečního kolíku
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);  // Přidej disk na cílový kolík
}

// Funkce pro zobrazení aktuálního stavu věží
void zobrazVeze(const vector<vector<int>> &veze) {
    size_t maxHeight = 0;
    for (const auto &vez : veze) {
        if (vez.size() > maxHeight) {
            maxHeight = vez.size() + 1;
        }
    }

    // Vypiš věže odshora dolů
    for (size_t i = maxHeight; i > 0; i--) {
        for (const auto &vez : veze) {
            if (vez.size() >= i) {
                cout << setw(8) << string(vez[i - 1], '='); // Disk reprezentovaný počtem "="
            } else {
                cout << setw(8) << "|"; // Prázdné místo
            }
        }
        cout << endl;
    }
    // Základ věží
    cout << string(8, '-') << " " << string(8, '-') << " " << string(8, '-') << endl;
    cout << "    A       B       C    " << endl << endl;
}

// Rekurzivní řešení Hanoiských věží
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n == 1) {
        Tah tah = {veze[z - 'A'].back(), z, cil, veze}; // Ulož aktuální stav věží
        provedTah(veze, tah); // Proveď tah
        tah.stavVezi = veze; // Ulož aktualizovaný stav věží po tahu
        tahy.push_back(tah); // Přidej tah do seznamu
        return;
    }

    hanoi(n - 1, z, cil, pomocny, veze, tahy); // Přesuň n-1 disků na pomocný kolík
    hanoi(1, z, pomocny, cil, veze, tahy);    // Přesuň poslední disk na cílový kolík
    hanoi(n - 1, pomocny, z, cil, veze, tahy); // Přesuň n-1 disků z pomocného kolíku na cílový kolík
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte pocet disku: ";
    cin >> n;

    if (n <= 0) {
        cerr << "Chyba: Pocet disku musi byt kladne císlo." << endl;
        return 1;
    }

    vector<vector<int>> veze(3); // Tři kolíky: A, B, C
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i); // Naplň první kolík (A) disky od největšího po nejmenší
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (const Tah &tah : tahy) {
        cout << "Presun disk " << tah.disk << " z koliku " << tah.z << " na kolik " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení aktuálního stavu věží
    }

    int celkovyPocetTahu = pow(2, n) -1;
    cout << "Celkovy pocet presunu je: " << celkovyPocetTahu << endl;

    return 0;
}
#endif // __TEST__