#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>>& veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);
    tah.stavVezi = veze;
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy) {
    if (n == 1) {
        Tah tah = { n, z, cil, veze };
        provedTah(veze, tah);
        tahy.push_back(tah);
    }
    else {
        hanoi(n - 1, z, cil, pomocny, veze, tahy);
        Tah tah = { n, z, cil, veze };
        provedTah(veze, tah);
        tahy.push_back(tah);
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

// Funkce pro zobrazení věží
void zobrazVeze(vector<vector<int>>& veze) {
    int maxHeight = 0;
    for (const auto& vezeColumn : veze) {
        if (vezeColumn.size() > maxHeight) {
            maxHeight = vezeColumn.size();
        }
    }

    for (int i = maxHeight - 1; i >= 0; --i) {
        for (const auto& vezeColumn : veze) {
            if (i < vezeColumn.size()) {
                cout << string(10 - vezeColumn[i], ' ') << string(vezeColumn[i] * 2 - 1, '=') << string(10 - vezeColumn[i], ' ');
            }
            else {
                cout << string(19, ' ');
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << string(19, '-') << " " << string(19, '-') << " " << string(19, '-') << endl;
    cout << "        A                  B                  C        " << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    if (n <= 0) {
        cout << "Neplatný počet disků." << endl;
        return 1;
    }

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (Tah tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
