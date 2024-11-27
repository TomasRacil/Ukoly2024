#include <iostream>
#include <vector>
#include <stdexcept>



using namespace std;

struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi;
};

void provedTah(vector<vector<int>> &veze, Tah tah) {
    // Najít disk na zdrojovém kolíku
    int zdrojIndex = tah.z - 'A';
    int cilIndex = tah.na - 'A';

    // Přesunout disk
    if (!veze[zdrojIndex].empty()) {
        int disk = veze[zdrojIndex].back();
        veze[zdrojIndex].pop_back();
        veze[cilIndex].push_back(disk);} else {
            throw runtime_error("Nelze presunout disk z prazdneho koliku");
        }
}
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n == 1) {
        // Vytvoření nového tahu
        Tah tah = {1, z, cil, veze}; // Uložení aktuálního stavu věží
        provedTah(veze, tah);

        // Uložení aktuálního stavu věží
        tah.stavVezi = veze;
        tahy.push_back(tah);
        return;
    }

    // Rekurzivní řešení pro n-1 disků
    hanoi(n-1, z, cil, pomocny, veze, tahy);

    // Přesun největšího disku
    Tah tah = {n, z, cil, veze}; // Uložení aktuálního stavu věží
    provedTah(veze, tah);

    // Uložení aktuálního stavu věží
    tah.stavVezi = veze;
    tahy.push_back(tah);

    // Přesun zbývajících disků
    hanoi(n-1, pomocny, z, cil, veze, tahy);
}

void zobrazVeze(vector<vector<int>> &veze) {
    // Najít maximální výšku věží
    int maxVyska = 0;
    for (const auto &vez : veze) {
        maxVyska = max(maxVyska, (int)vez.size());
    }

    // Zobrazení věží odshora dolů
    for (int vyska = maxVyska - 1; vyska >= 0; vyska--) {
        for (int vez = 0; vez < 3; vez++) {
            if (vyska < veze[vez].size()) {
                cout << " [" << veze[vez][vyska] << "] ";
            } else {
                cout << "  |  ";
            }
        }
        cout << endl;
    }
    cout << "  A    B    C  " << endl;
    cout << "-------------------" << endl;
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
    for (Tah tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
