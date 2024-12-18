#include <iostream>   // Zahrnutí hlavičkového souboru pro vstup a výstup
#include <vector>     // Zahrnutí hlavičkového souboru pro práci s vektory
#include <iomanip>    // Zahrnutí hlavičkového souboru pro formátovaný výstup

using namespace std;  // Použití jmenného prostoru std pro zjednodušení zápisu

// Struktura pro reprezentaci tahu v Hanojských věžích
struct Tah {
    int disk;                   // Číslo disku, který se přesouvá
    char z;                     // Počáteční věž ('A', 'B' nebo 'C')
    char na;                    // Cílová věž ('A', 'B' nebo 'C')
    vector<vector<int>> stavVezi; // Stav všech věží po provedení tahu
};

// Funkce pro provedení tahu mezi věžemi
void provedTah(vector<vector<int>> &veze, Tah &tah) {
    // Kontrola, zda je počáteční věž prázdná
    if (veze[tah.z - 'A'].empty()) {
        throw runtime_error("Chyba: Věž " + string(1, tah.z) + " je prázdná, nelze provést tah.");
    }

    // Odebrání disku z počáteční věže
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();

    // Přidání disku na cílovou věž
    veze[tah.na - 'A'].push_back(disk);

    // Uložení stavu věží po provedení tahu
    tah.disk = disk;
    tah.stavVezi = veze;
}

// Rekurzivní funkce pro řešení Hanojských věží
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    // Pokud je počet disků neplatný (n <= 0), funkce nic neprovede
    if (n <= 0) {
        return;
    }

    // Inicializace věží, pokud jsou všechny prázdné
    if (veze[0].empty() && veze[1].empty() && veze[2].empty()) {
        for (int i = n; i > 0; i--) {
            veze[0].push_back(i); // Naplnění první věže (A) disky od největšího po nejmenší
        }
    }

    // Základní případ: přesun jednoho disku
    if (n == 1) {
        Tah tah = {0, z, cil, {}}; // Vytvoření struktury pro tah
        provedTah(veze, tah);      // Provedení tahu
        tahy.push_back(tah);       // Uložení tahu do seznamu tahů
    } else {
        // Rekurzivní přesun n-1 disků na pomocnou věž
        hanoi(n - 1, z, cil, pomocny, veze, tahy);
        // Přesun největšího disku na cílovou věž
        Tah tah = {0, z, cil, {}};
        provedTah(veze, tah);
        tahy.push_back(tah);
        // Rekurzivní přesun n-1 disků z pomocné věže na cílovou věž
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

// Funkce pro zobrazení aktuálního stavu věží v konzoli
void zobrazVeze(const vector<vector<int>> &veze) {
    // Kontrola, zda jsou věže neprázdné
    if (veze.empty()) {
        cout << "Žádné věže k zobrazení." << endl;
        return;
    }

    int maxHeight = 0; // Proměnná pro zjištění maximální výšky věže
    // Zjištění nejvyšší věže
    for (const auto &vez : veze) {
        maxHeight = max(maxHeight, static_cast<int>(vez.size()));
    }

    // Výpis věží odshora dolů
    for (int i = maxHeight - 1; i >= 0; --i) {
        for (const auto &vez : veze) {
            if (i < vez.size()) {
                cout << setw(5) << vez[i]; // Výpis disku
            } else {
                cout << setw(5) << "|";    // Prázdné místo ve věži
            }
        }
        cout << endl;
    }

    // Označení věží
    cout << "  A    B    C  " << endl;
    cout << endl;
}

#ifndef __TEST__ // Podmíněná kompilace: následující kód se přeloží pouze, pokud není definován __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;

    // Kontrola platnosti zadaného počtu disků
    if (n <= 0) {
        cout << "Počet disků musí být kladné číslo." << endl;
        return 1; // Ukončení programu s chybovým kódem
    }

    vector<vector<int>> veze(3); // Vytvoření tří věží jako vektorů
    // Naplnění první věže (A) disky od největšího po nejmenší
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy); // Řešení Hanojských věží

    // Zobrazení všech tahů a stavu věží po každém tahu
    for (const Tah &tah : tahy) {
        cout << "Přesun disku " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0; // Úspěšné ukončení programu
}
#endif // __TEST__
