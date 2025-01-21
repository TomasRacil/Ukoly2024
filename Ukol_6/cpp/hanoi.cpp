#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi;
};


void provedTah(vector<vector<int>> &veze, Tah &tah) {

    if (veze[tah.z - 'A'].empty()) {
        throw runtime_error("Nastala chyba: Věž " + string(1, tah.z) + " je prázdná, nelze provést další krok.");
    }


    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();


    veze[tah.na - 'A'].push_back(disk);


    tah.disk = disk;
    tah.stavVezi = veze;
}


void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {

    if (n <= 0) {
        return;
    }


    if (veze[0].empty() && veze[1].empty() && veze[2].empty()) {
        for (int i = n; i > 0; i--) {
            veze[0].push_back(i);
        }
    }


    if (n == 1) {
        Tah tah = {0, z, cil, {}};
        provedTah(veze, tah);
        tahy.push_back(tah);
    } else {

        hanoi(n - 1, z, cil, pomocny, veze, tahy);

        Tah tah = {0, z, cil, {}};
        provedTah(veze, tah);
        tahy.push_back(tah);

        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}


void zobrazVeze(const vector<vector<int>> &veze) {

    if (veze.empty()) {
        cout << "Žádné věže k zobrazení." << endl;
        return;
    }

    int maxHeight = 0;

    for (const auto &vez : veze) {
        maxHeight = max(maxHeight, static_cast<int>(vez.size()));
    }


    for (int i = maxHeight - 1; i >= 0; --i) {
        for (const auto &vez : veze) {
            if (i < vez.size()) {
                cout << setw(5) << vez[i];
            } else {
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
    cout << "Zadejte počet disků: ";
    cin >> n;


    if (n <= 0) {
        cout << "Počet disků musí být větší než nula." << endl;
        return 1;
    }

    vector<vector<int>> veze(3);

    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy;
    hanoi(n, 'A', 'B', 'C', veze, tahy);


    for (const Tah &tah : tahy) {
        cout << "Přesun disku " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi);
    }

    return 0;
}
#endif // __TEST__
