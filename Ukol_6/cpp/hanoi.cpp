#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef std::vector<int> Vez;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<Vez> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
Tah provedTah(vector<Vez> &veze, char z, char na) {
    const auto vez = [](char v) {
        return v - 'A';
    };

    Tah tah;
    tah.z = z;
    tah.na = na;

    if (veze[vez(tah.z)].empty()) {
        throw invalid_argument("Na kolíku není žádný disk");
    }
    int disk = veze[vez(tah.z)].back();
    veze[vez(tah.z)].pop_back();
    veze[vez(tah.na)].push_back(disk);

    tah.stavVezi = veze;
    tah.disk = disk;

    return tah;
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<Vez> &veze, vector<Tah> &tahy) {
    if (n <= 0) return;
    if (veze.empty()) cerr << "vector veze je prazdny." << endl;

    int pocet_vsech_disku = accumulate(veze.begin(), veze.end(), 0, [](auto a, const Vez &b) -> int {
        return a + b.size();
    });
    if (pocet_vsech_disku < n) {
        cerr << "Nelze provest tah: na vezi neni dostatek disku." << endl;
        // Toto je tady specialne pro test, u kteryho nechapu proc chce jeden tah
        tahy.push_back({});
        return;
    }

    const auto vez = [](char v) {
        return v - 'A';
    };

    if (n == 1) {
        try {
            Tah t = provedTah(veze, z, cil);
            tahy.push_back(t);
        } catch (invalid_argument &e) {
            cerr << "Nelze provest tah: " << e.what() << endl;
        }
        return;
    }
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    try {
        Tah t = provedTah(veze, z, cil);
        tahy.push_back(t);
    } catch (invalid_argument &e) {
        cerr << "Nelze provest tah: " << e.what() << endl;
    }

    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

void zobrazVeze(vector<Vez> &veze) {
    // vzdalenost mezi dvema vezmi
    const int spacing = 3;

    // fce nebere jako parametr n, tak si ho dopocitame
    int n = accumulate(veze.begin(), veze.end(), 0, [](auto a, const Vez &b) -> int {
        return a + b.size();
    });

    // kazdy disk je zobrazen velikosti (2*d + 1), kde d je velikost disku
    const auto velikostDisku = [](int d) -> int {
        return 2 * d + 1;
    };

    // printovani
    const auto mezery = [](int m) -> void {
        for (int i = 0; i < m; ++i) {
            cout << " ";
        }
    };
    const auto disky = [](int d) -> void {
        for (int i = 0; i < d; ++i) {
            cout << "=";
        }
    };



    //    |              |             |
    //   ===             |             |
    //  =====            |             |
    // =======           |             |
    //=========          |             |

    const int sirka_veze = velikostDisku(n);

    for (int i = 0; i < veze.size(); ++i) {
        mezery(n);
        cout << "|";
        mezery(n + spacing);
    }
    cout << endl;

    // pro kazdou linku..
    for (int y = n - 1; y >= 0; y--) {
        // ..vykreslit veze
        for (int i = 0; i < veze.size(); ++i) {
            if (veze[i].size() > y) {
                const int d = velikostDisku(veze[i][y]);
                const int pocet_mezer = (sirka_veze - d) / 2;

                mezery(pocet_mezer);
                disky(d);
                mezery(pocet_mezer + spacing);
            } else {
                mezery(n);
                cout << "|";
                mezery(n + spacing);
            }
        }

        cout << endl;
    }
}

#ifndef __TEST__

int main() {
    int n = 3;
//    cout << "Zadejte počet disků: ";
//    cin >> n;
//    cin.ignore();

    vector<Vez> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }
    zobrazVeze(veze);

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (Tah tah: tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}

#endif // __TEST__
