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

    int zIndex = tah.z - 'A';
    int naIndex = tah.na - 'A';

    int disk = veze[zIndex].back();
    veze[zIndex].pop_back();
    veze[naIndex].push_back(disk);


    tah.stavVezi = veze;
}


void zobrazVeze(vector<vector<int>> &veze) {

    int maxDisk = 0;

    for (auto &vez : veze) {
        for (int disk : vez) {
            maxDisk = max(maxDisk, disk);
        }
    }

    int width = maxDisk * 2 + 1;
    int baseWidth = width+2;
    int maxHeight = maxDisk ;

    for (int i = maxHeight; i >= 0; --i) {
        for (auto &vez : veze) {
            if (i < vez.size()) {

                int disk = vez[i];
                int padding = maxDisk - disk;
                cout << " " << string(padding, '   ') << string(disk * 2 - 1, '=') << string(padding, '   ') << " ";

            } else {

                cout << string(maxDisk, '   ') << "|" << string(maxDisk, '   ');
            }

            cout << "   ";

        }
        cout << endl;
    }


    for (int i = 0; i < 3; ++i) {
        cout << string(baseWidth-2, '-') << "   ";
    }

    cout << endl;


    cout << setw((baseWidth-1)/2) << "A" << "   " << setw(baseWidth-2) << "B" << "   "<< setw(baseWidth-2) << "C" << endl;
}



void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {

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


#ifndef __TEST__
int main() {
    
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;

    if (n <= 0) {
        cout << "Počet disků musí být kladné celé číslo!" << endl;
        return 1;
    }

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    cout << endl << "Počáteční stav věží:" << endl;

    zobrazVeze(veze);

    vector<Tah> tahy;


    hanoi(n, 'A', 'B', 'C', veze, tahy);


    for (Tah tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl << endl;
        zobrazVeze(tah.stavVezi);
    }

    return 0;
}
#endif // __TEST__
