#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <numeric> // Include for accumulate

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Typ pro reprezentaci věže
using Vez = vector<int>;

// Funkce pro provedení tahu
void provedTah(vector<Vez>& veze, Tah& tah) {
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);
    tah.stavVezi = veze;
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<Vez>& veze, vector<Tah>& tahy) {
    if (n <= 0) return;
    if (veze.empty()) {
        cerr << "vector veze je prazdny." << endl;
        return;
    }

    int pocet_vsech_disku = accumulate(veze.begin(), veze.end(), 0, [](auto a, const Vez& b) -> int {
        return a + b.size();
    });
    if (pocet_vsech_disku < n) {
        cerr << "Nelze provest tah: na vezi neni dostatek disku." << endl;
        tahy.push_back({});
        return;
    }

    if (n == 1) {
        try {
            Tah t = { veze[z - 'A'].back(), z, cil, {} };
            provedTah(veze, t);
            tahy.push_back(t);
        }
        catch (invalid_argument& e) {
            cerr << "Nelze provest tah: " << e.what() << endl;
        }
        return;
    }
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    try {
        Tah t = { veze[z - 'A'].back(), z, cil, {} };
        provedTah(veze, t);
        tahy.push_back(t);
    }
    catch (invalid_argument& e) {
        cerr << "Nelze provest tah: " << e.what() << endl;
    }

    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

// Funkce pro zobrazení věží
void zobrazVeze(const vector<Vez>& veze) {
    int max_height = 0;
    for (const auto& vez : veze) {
        max_height = max(max_height, (int)vez.size());
    }

    for (int i = max_height - 1; i >= 0; --i) {
        for (const auto& vez : veze) {
            if (i < vez.size()) {
                cout << string(max_height - vez[i], ' ') << string(vez[i], '=') << string(max_height - vez[i], ' ') << " ";
            }
            else {
                cout << string(max_height, ' ') << "|" << string(max_height, ' ') << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

#ifndef __TEST__
int main() {
    // Set locale to UTF-8
    locale::global(locale(locale(), new codecvt_utf8<wchar_t>));
    wcout.imbue(locale());

    int n;
    wcout << L"Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    if (n <= 0) {
        wcout << L"Neplatný počet disků." << endl;
        return 1;
    }

    vector<Vez> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (const Tah& tah : tahy) {
        wcout << L"Přesuň disk " << tah.disk << L" z kolíku " << tah.z << L" na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
