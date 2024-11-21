#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

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
// Function to solve the Tower of Hanoi puzzle
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    // If the number of disks is zero or negative, do nothing
    if (n <= 0) return;

    // Base case: if there's only one disk to move
    if (n == 1) {
        Tah tah = {veze[z - 'A'].back(), z, cil};
        provedTah(veze, tah);
        tahy.push_back(tah);  // Add the move to the list
    } else {
        // Recursive case: move n-1 disks to the auxiliary pole
        hanoi(n - 1, z, cil, pomocny, veze, tahy);

        // Move the nth disk to the target pole
        Tah tah = {veze[z - 'A'].back(), z, cil};
        provedTah(veze, tah);
        tahy.push_back(tah); // Add the move to the list

        // Move the n-1 disks from the auxiliary pole to the target pole
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}
void zobrazVeze(const vector<vector<int>> &veze) {
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
    cout << "  A    B    C  " << endl << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte pocet disku: ";
    cin >> n;

    if (n <= 0) {
        cout << "Pocet disku musi byt kladne cislo." << endl;
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
        cout << "Presun disk " << tah.disk << " z koliku " << tah.z << " na kolik " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
