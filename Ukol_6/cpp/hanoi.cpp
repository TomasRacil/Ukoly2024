#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>
#include <codecvt>

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
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);
    tah.stavVezi = veze;
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n <= 0) {
        throw invalid_argument("Počet disků musí být kladné číslo.");
    }
    if (n == 1) {
        Tah tah = {n, z, cil, veze};
        provedTah(veze, tah);
        tahy.push_back(tah);
    } else {
        hanoi(n - 1, z, cil, pomocny, veze, tahy);
        Tah tah = {n, z, cil, veze};
        provedTah(veze, tah);
        tahy.push_back(tah);
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

// Funkce pro zobrazení věží
void zobrazVeze(const vector<vector<int>> &veze) {
    int max_height = 0;
    for (const auto &veze : veze) {
        max_height = max(max_height, (int)veze.size());
    }

    for (int i = max_height - 1; i >= 0; --i) {
        for (const auto &veze : veze) {
            if (i < veze.size()) {
                cout << string(max_height - veze[i], ' ') << string(veze[i], '=') << string(max_height - veze[i], ' ') << " ";
            } else {
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

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (const Tah &tah : tahy) {
        wcout << L"Přesuň disk " << tah.disk << L" z kolíku " << tah.z << L" na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
