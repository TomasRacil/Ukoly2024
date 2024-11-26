#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    std::vector<std::vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(std::vector<std::vector<int>>& veze, Tah tah) {
    int from, to;
    from = toupper(tah.z) - 'A'; // index veže z charu věže
    to = toupper(tah.na) - 'A';
    veze[to].push_back(veze[from].back()); // přesun
    veze[from].pop_back(); // odstranění

}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, std::vector<std::vector<int>>& veze, std::vector<Tah>& tahy) {
    if (n <= 0) {
        std::cout << "Error! Zadej číslo větší jak 0";
        return;
    }
    else if (n == 1) { // ošetření pro jeden disk
        provedTah(veze, { n, z, cil} );
        tahy.push_back({n,z,cil, veze}); // push pro následný výpis
        return;
    }
    else {
        hanoi(n - 1, z, cil, pomocny, veze, tahy); // rekurzivní přesouvání disků na cílovou věž
        provedTah(veze, {n, z, cil, veze}); // Přesunout n-tý disk na cílový kolík
        tahy.push_back({ n,z,cil, veze }); // exp. konstruktor a uložení stavu
        hanoi(n - 1, pomocny, z, cil, veze, tahy); // rekurzivní přesouvání disků na pomocnou věž
    }
}

void zobrazVeze(std::vector<std::vector<int>>& veze) { // vypis s jednoduchou vyzualizací přesunu
    for (int i = 0; i < 3; i++) {
        std::cout << "Kolik " << char('A' + i) << ": \n";
        for (int j = veze[i].size()-1; j >= 0; j--) {
            for (int k = 1; k <= veze[i][j]; k++) {
                std::cout << "* ";
            }
            std::cout << "\n";

        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

#ifndef __TEST__
int main() {
    int n;
    std::cout << "Zadejte počet disků: ";
    std::cin >> n;
    std::cin.ignore();
    if (n >= 0)
    {    std::vector<std::vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    std::vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (Tah tah : tahy) {
        std::cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << "\n";
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }
    }
    return 0;
}
#endif // __TEST__
