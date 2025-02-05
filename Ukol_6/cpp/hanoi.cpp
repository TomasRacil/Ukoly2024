#include <iostream>
#include <vector>

using namespace std;


struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi;
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);
}


void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n <= 0) return;

    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    Tah tah;
    tah.disk = n;
    tah.z = z;
    tah.na = cil;
    tah.stavVezi = veze;

    if (veze[z - 'A'].empty() || veze[z - 'A'].back() != n) {
        veze[z - 'A'].push_back(n); 
    }

    provedTah(veze, tah);
    tah.stavVezi = veze; 
    tahy.push_back(tah);

    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}





void zobrazVeze(vector<vector<int>> &veze) {
    int maxHeight = 0;
    for (const auto &vez : veze) {
        if (vez.size() > maxHeight) {
            maxHeight = vez.size();
        }
    }
    for (int i = maxHeight - 1; i >= 0; --i) {
        for (const auto &vez : veze) {
            if (i < vez.size()) {
                cout << vez[i] << "\t";
            } else {
                cout << "|\t";
            }
        }
        cout << endl;
    }
    cout << "A\tB\tC" << endl << endl;
}

#ifndef __TEST__
int main()
{
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (Tah tah : tahy)
    {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
