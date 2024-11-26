#include <iostream>
#include <vector>

using namespace std;


// Struktura pro reprezentaci tahu
struct Tah {
    int disk; // Číslo disku
    char z; // Zdrojová věž
    char na; // Cílová věž
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah) {


    int disk = tah.disk; // Disk ktery se presouva
    int from_index = tah.z - 'A';  // Index zdrojové věže
    int to_index = tah.na - 'A';  // Index cílové věže

    // Zkontroluj, zda jsou indexy ve správném rozsahu
    if (from_index < 0 || from_index >= (int)veze.size() || to_index < 0 || to_index >= (int)veze.size()) {
        cout << "Error: Neplatny index" << tah.z << " to " << tah.na << endl;
        return;
    }

    // Zkontroluj, zda je zdrojová věž neprázdná
    if (veze[from_index].empty()) {
        cout << "Vez " << tah.z << " je prazdna" << endl;
        return;
    }

    // Proveď tah
    veze[from_index].pop_back();
    veze[to_index].push_back(disk);
}


// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
// n = pocet disku
    if (n <= 0){
        return; // Pokud je pocet disku neg nebo 0 tak skonči
    }

    if(veze[0].empty() && veze[1].empty() && veze[2].empty()){
        for (int i = n; i > 0; i--) {
            veze[0].push_back(i); //Pridej disky na prvni vez pokud se stala chyba v prubehu
        }
    }

    // Pokud je n == 1 tak presun disk na cilovou vez
    if (n == 1) {
        if (veze[z - 'A'].empty()) {
            cout << "Vez " << z << " je prazdna" << endl;
            return;

        }
        int disk = veze[z - 'A'].back(); // Disk ktery se presouva
        provedTah(veze, {disk, z, cil, veze}); // Proveď tah
        tahy.push_back({disk, z, cil, veze}); // Zaznamenej tah
        return;
    }
    hanoi(n - 1, z, cil, pomocny, veze, tahy); // Přesun n-1 disků z pomocné na cílovou věž
    // Pokud je zdrojova vez prazdna tak skonci
    if (veze[z - 'A'].empty()) {
        return;
    }
    int disk = veze[z - 'A'].back(); // Disk ktery se presouva
    provedTah(veze, {disk, z, cil, veze}); // Proveď tah

    Tah tah = {disk, z, cil, veze}; // Zaznamenej tah
    tahy.push_back(tah); // Přidej tah do vektoru

    hanoi(n - 1, pomocny, z, cil, veze, tahy); // Přesun n-1 disků z pomocné na cílovou věž
}

// Funkce pro zobrazení stavu věží
void zobrazVeze(vector<vector<int>> &veze) {
    int max_height = 0;
    for (const auto &vez : veze) {
        if (vez.size() > max_height) {
            max_height = vez.size();
        }
    }

    for (int level = max_height - 1; level >= 0; --level) {
        for (const auto &vez : veze) {
            if (level < vez.size()) {
                cout << vez[level] << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    cout << "A B C" << endl;
}



#ifndef __TEST__

int main() {
    int n; // Pocet disku
    cout << "Zadejte pocet disku (max 15): ";
    cin >> n ; // Nacti pocet disku
    cin.ignore(); // Ignorovani zbytku radku
    // teoreticky by mohlo byt vice nez 15 disku, ale vypocet by trval prilis dlouho
    if (n > 15) {
        cerr << "Pocet disku muze byt max 15" << endl;
        return 1;
    }
    if (cin.fail()) {
        cout << "Nespravny vstup." << endl;
        return 1;
    }


    vector<vector<int>> veze(3); // vektor vektoru pro reprezentaci věží (matice 3xN)
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i); //Pridej disky na prvni vez
    }

    vector<Tah> tahy; // Vektor pro uložení tahů

    zobrazVeze(veze); // Zobrazení stavu věží na začátku

    try {
        hanoi(n, 'A', 'B', 'C', veze, tahy); // Vyřešení hanoi
    } catch (const std::exception &e) {
        cerr << "Chyba pri reseni: " << e.what() << endl;
        return 1;
    }

    // Zobrazení tahů a stavů věží
    int tahCount = 1; // Pocitadlo tahu
    for (Tah tah: tahy) {
        cout << "Tah: " << tahCount << endl; // tah cislo: tahCount
        cout << "Presun disk " << tah.disk << " z koliku " << tah.z << " na kolik " << tah.na << endl;
        tahCount++;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}

#endif // __TEST__