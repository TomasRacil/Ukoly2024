#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;                    // Disk being moved
    char z;                      // Source peg
    char na;                     // Destination peg
    vector<vector<int>> stavVezi; // State of the towers after the move
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back(); // Get the top disk from the source peg
    veze[tah.z - 'A'].pop_back();       // Remove the disk from the source peg
    veze[tah.na - 'A'].push_back(disk); // Place the disk on the target peg
}

// Rekurzivní řešení Hanoiských věží
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    if (n <= 0) return; // Base case: no disks to move
    
    hanoi(n - 1, z, cil, pomocny, veze, tahy); // Move n-1 disks to the auxiliary peg

    // Move the nth disk to the destination peg
    Tah tah;
    tah.disk = n;
    tah.z = z;
    tah.na = cil;
    tah.stavVezi = veze; 
    provedTah(veze, tah); // Perform the move
    tah.stavVezi = veze; // Record the new state
    tahy.push_back(tah); // Log the move

    hanoi(n - 1, pomocny, z, cil, veze, tahy); // Move n-1 disks to the destination peg
}

// Funkce pro zobrazení věží
void zobrazVeze(const vector<vector<int>> &veze) {
    int maxHeight = 0;
    for (const auto &vez : veze) {
        maxHeight = max(maxHeight, static_cast<int>(vez.size())); // Find the tallest peg
    }

    for (int i = maxHeight - 1; i >= 0; --i) {
        for (const auto &vez : veze) {
            if (i < vez.size()) {
                cout << vez[i] << "\t"; // Print disk number
            } else {
                cout << "|\t";          // Print empty spot
            }
        }
        cout << endl;
    }
    cout << "A\tB\tC" << endl << endl; // Label the pegs
}


#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    vector<vector<int>> veze(3); // Initialize the towers as vectors of vectors
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i); // Add all disks to the first peg
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy); // Solve the Towers of Hanoi problem

    // Zobrazení tahů a stavů věží
    for (const Tah &tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Display the state of the towers after the move
    }

    return 0;
}
#endif // __TEST__
