#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;  // Kolík, ze kterého se disk přesouvá
    char na; // Kolík, na který se disk přesouvá
    vector<vector<int>> stavVezi; // Stav věží po provedení tahu
};

// Funkce pro provedení tahu - aktualizuje stav věží
void provedTah(vector<vector<int>>& veze, Tah tah) {
    int zdrojIndex = tah.z - 'A';  // Index zdrojového kolíku
    int cilIndex = tah.na - 'A';   // Index cílového kolíku


    int disk = veze[zdrojIndex].back();  //vrchni disk
    veze[zdrojIndex].pop_back();
    veze[cilIndex].push_back(disk);
}

// Funkce pro řešení Hanoiských věží pomocí rekurze
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy) {
    if (n <= 0) {
        return;
    }
    if (veze[0].empty() && veze[1].empty() && veze[2].empty())
      for(int i = n; i > 0; i--)
        veze[0].push_back(i);



    // Rekurzivní řešení pro n-1
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    // Přesun největšího disku
    Tah tah = { n, z, cil, veze };
    provedTah(veze, tah);
    tah.stavVezi = veze;
    tahy.push_back(tah);

    // Přesun zbývajících disků
    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

// Funkce pro zobrazení aktuálního stavu věží
void zobrazVeze(vector<vector<int>>& veze) {
    int maxVyska = 0;
    // Najít maximální výšku věží
    for (const auto& vez : veze) {
        maxVyska = max(maxVyska, (int)vez.size());
    }

    // Zobrazení věží odshora dolů
    for (int vyska = maxVyska - 1; vyska >= 0; vyska--) {
        for (int vez = 0; vez < 3; vez++) {
            if (vyska < veze[vez].size()) {
                cout << " [" << veze[vez][vyska] << "] ";
            }
            else {
                cout << "  |  "; // Pokud není disk, zobrazí se prázdné místo
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

    // Pokud je zadán neplatný počet disků, použijeme hodnotu 1
    if (n <= 0) {
        cerr << "Varování: Počet disků musí být kladné číslo. Používám hodnotu 1." << endl;
        n = 1;
    }

    // Inicializace věží
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
