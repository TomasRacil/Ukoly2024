#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>>& veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back(); // Disk, který přesouváme
    veze[tah.z - 'A'].pop_back();       // Odstraníme disk z výchozí věže
    veze[tah.na - 'A'].push_back(disk); // Přidáme disk na cílovou věž
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy) {
    if (n == 0) return;

    // Přesuň n-1 disků na pomocný kolík
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    // Přesuň největší disk z výchozí věže na cílovou
    Tah tah = { veze[z - 'A'].back(), z, cil, veze };
    provedTah(veze, tah); // Proveď tah
    tah.stavVezi = veze;  // Ulož stav věží po tahu
    tahy.push_back(tah);  // Přidej tah do seznamu

    // Přesuň n-1 disků z pomocného kolíku na cílový
    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

// Funkce pro vizualizaci věží
void zobrazVeze(const vector<vector<int>>& veze) {
    int maxVyska = 0;

    // Najdi nejvyšší věž pro správné počty řádků
    for (const auto& vez : veze)
        maxVyska = max(maxVyska, static_cast<int>(vez.size()));

    // Vypiš věže řádek po řádku odshora dolů
    for (int i = maxVyska - 1; i >= 0; --i) {
        for (const auto& vez : veze) {
            if (i < static_cast<int>(vez.size())) {
                int disk = vez[i];
                int mezera = (9 - (disk * 2 - 1)) / 2; // Výpočet mezer kolem disku
                cout << string(mezera, ' ') << string(disk * 2 - 1, '=') << string(mezera, ' ');
            }
            else {
                cout << string(9, ' '); // Prázdná věž
            }
            cout << " "; // Mezery mezi věžemi
        }
        cout << endl;
    }

    // Vypiš základnu věží
    cout << string(9, '-') << " " << string(9, '-') << " " << string(9, '-') << endl;

    // Popisky věží
    cout << setw(5) << "A" << setw(11) << "B" << setw(11) << "C" << endl
        << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (Tah tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }
    cout << "Problém vyřešen v " << tahy.size() << " tazích." << endl;

    return 0;
}
#endif // __TEST__


// cd Ukol_6/cpp && mkdir -p build && cd build && cmake .. && make && ./mytests

/*
 The C compiler identification is GNU 10.2.1
-- The CXX compiler identification is GNU 10.2.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found GTest: /usr/lib/x86_64-linux-gnu/libgtest.a  
-- Configuring done
-- Generating done
-- Build files have been written to: /workspaces/Ukoly2024/Ukol_6/cpp/build
Scanning dependencies of target mytests
[ 25%] Building CXX object CMakeFiles/mytests.dir/test.cpp.o
[ 50%] Linking CXX executable mytests
[ 50%] Built target mytests
Scanning dependencies of target hanoi
[ 75%] Building CXX object CMakeFiles/hanoi.dir/hanoi.cpp.o
[100%] Linking CXX executable hanoi
[100%] Built target hanoi
Running main() from /build/googletest-YnT0O3/googletest-1.10.0.20201025/googletest/src/gtest_main.cc
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from HanoiTest
[ RUN      ] HanoiTest.JedenDisk
[       OK ] HanoiTest.JedenDisk (0 ms)
[ RUN      ] HanoiTest.DvaDisky
[       OK ] HanoiTest.DvaDisky (0 ms)
[ RUN      ] HanoiTest.TriDisky
[       OK ] HanoiTest.TriDisky (0 ms)
[ RUN      ] HanoiTest.InvalidNumberOfDisks
Segmentation fault (core dumped)
*/