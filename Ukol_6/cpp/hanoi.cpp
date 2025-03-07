#include <iostream>
#include <vector>
#include <algorithm> // std::max
#include <cstdlib>   // pro exit() v případě chyb

using namespace std;

// Struktura pro reprezentaci jednoho tahu
struct Tah {
    int disk;                  // číslo disku, který se přesouvá
    char z;                    // z jakého kolíku
    char na;                   // na jaký kolík
    vector<vector<int>> stavVezi; // uložení stavu všech třech věží PO provedení tahu
};

// Pomocná funkce pro převod znaku kolíku na index do "veze" (0 = A, 1 = B, 2 = C)
int kolikToIndex(char c) {
    switch (c) {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
    }
    // Neočekávaný vstup - můžete ošetřit vyhozením výjimky či chybovou hláškou
    return -1;
}

// Funkce pro provedení jednoho tahu
void provedTah(vector<vector<int>> &veze, Tah tah) {
    int from = kolikToIndex(tah.z);
    int to   = kolikToIndex(tah.na);

    // Pokud by indexy byly -1, byl by to neplatný tah
    if (from < 0 || from > 2 || to < 0 || to > 2) {
        cerr << "Chyba: neplatné označení kolíku." << endl;
        return;
    }
    if (veze[from].empty()) {
        cerr << "Chyba: snažíte se sebrat disk z prázdného kolíku." << endl;
        return;
    }

    // Sejmeme disk z "from" a položíme ho na "to"
    int presouvanyDisk = veze[from].back();
    veze[from].pop_back();

    // Zkontrolujeme, zda nedáváme větší disk na menší
    if (!veze[to].empty()) {
        int vrchniDisk = veze[to].back();
        if (presouvanyDisk > vrchniDisk) {
            cerr << "Chyba: větší disk nelze položit na menší." << endl;
            // Můžeme buď skončit, nebo disk vrátit zpět na původní věž
            veze[from].push_back(presouvanyDisk);
            return;
        }
    }
    veze[to].push_back(presouvanyDisk);
}

// Rekurzivní řešení Hanoiských věží: přesune n disků z kolíku z na kolík cil,
// za pomoci kolíku pomocny. Současně ukládá všechny tahy do vektoru "tahy".
void hanoi(int n, char z, char pomocny, char cil,
           vector<vector<int>> &veze,
           vector<Tah> &tahy)
{
    if (n <= 0) return; // pokud je n <= 0, neděláme nic

    // Přesun n-1 disků z kolíku z na kolík pomocny (využijeme cil jako "pomocný")
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    // Přesun posledního (největšího) disku z kolíku z na kolík cil
    {
        Tah t;
        t.disk = n;
        t.z = z;
        t.na = cil;

        // Proveď tah
        provedTah(veze, t);

        // Ulož stav věží po tahu
        t.stavVezi = veze;

        // Přidáme do vektoru tahů
        tahy.push_back(t);
    }

    // Přesun n-1 disků z kolíku pomocny na kolík cil (využijeme z jako "pomocný")
    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

// Funkce pro vypsání aktuálního stavu věží do konzole
// Věž A = veze[0], Věž B = veze[1], Věž C = veze[2].
void zobrazVeze(const vector<vector<int>> &veze)
{
    // Najdeme nejvyšší počet disků na kterékoli věži
    int maxDisku = 0;
    for (int i = 0; i < 3; i++) {
        if (veze[i].size() > (size_t)maxDisku) {
            maxDisku = (int)veze[i].size();
        }
    }

    // Tiskneme odshora dolů, řádek po řádku
    // Řádek "nahoře" = index = maxDisku - 1, dole = index = 0
    for (int radek = maxDisku - 1; radek >= 0; radek--) {
        // Každá věž v jednom sloupci
        for (int i = 0; i < 3; i++) {
            if ((int)veze[i].size() > radek) {
                // Věž i má na daném "patře" disk
                int disk = veze[i][radek];
                cout << disk << "\t";
            } else {
                // Věž i je tady prázdná
                cout << "|\t";
            }
        }
        cout << endl;
    }
    // Oddělíme bloky prázdným řádkem
    cout << "---------------------------------------" << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;

    if (!cin || n < 1) {
        cerr << "Neplatný počet disků. Program bude ukončen." << endl;
        return 1;
    }

    // Vytvoříme 3 "věže" - každá je vektor disků (čísla disků 1..n)
    // veze[0] = kolík A, veze[1] = kolík B, veze[2] = kolík C
    vector<vector<int>> veze(3);

    // Na začátku jsou všechny disky na A (veze[0]) od největšího (dole) po nejmenší (nahoře)
    // Takže do veze[0] vkládáme n, n-1, ..., 2, 1
    for (int i = n; i >= 1; i--) {
        veze[0].push_back(i);
    }

    // Vektor tahů - v každém tahu uložíme info o disku a stav všech věží
    vector<Tah> tahy;

    // Spustíme rekurzivní algoritmus pro přesun z A na C
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Všechna řešení už máme v "tahy" (každý tah s popisem)
    // Vypíšeme je:
    for (size_t i = 0; i < tahy.size(); i++) {
        const Tah &t = tahy[i];
        cout << "Přesuň disk " << t.disk
             << " z kolíku " << t.z
             << " na kolík " << t.na << endl;
        zobrazVeze(t.stavVezi);
    }

    return 0;
}
#endif // __TEST__
