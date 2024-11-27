
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi;
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>>& veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back(); // Disk, který přesouváme
    veze[tah.z - 'A'].pop_back();       // Odstraníme disk z výchozí věže
    veze[tah.na - 'A'].push_back(disk); // Přidáme disk na cílovou věž
}

// Funkce pro řešení Hanoiských věží
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy) {
    if (n <= 0) {
        return; // Žádné tahy, pokud je počet disků 0 nebo záporný
    }

    if (n == 1) {
        // Přesuneme jediný disk z výchozí věže na cílovou
        Tah tah = {veze[z - 'A'].back(), z, cil, veze};
        provedTah(veze, tah);
        tah.stavVezi = veze;
        tahy.push_back(tah);
        return;
    }

    // Přesuň n-1 disků na pomocný kolík
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    // Proveď tah největšího disku
    Tah tah = {veze[z - 'A'].back(), z, cil, veze};
    provedTah(veze, tah);
    tah.stavVezi = veze;
    tahy.push_back(tah);

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
                int mezera = (9 - (disk * 2 - 1)) / 2;
                cout << string(mezera, ' ') << string(disk * 2 - 1, '=') << string(mezera, ' ');
            } else {
                cout << string(9, ' '); // Prázdná věž
            }
            cout << " ";
        }
        cout << endl;
    }

    // Základna věží
    cout << string(9, '-') << " " << string(9, '-') << " " << string(9, '-') << endl;
    cout << setw(5) << "A" << setw(11) << "B" << setw(11) << "C" << endl
         << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;

    if (n < 0) {
        cout << "Nelze zadávat záporná čísla." << endl;
        return 1;
    } else if (n == 0) {
        cout << "Počet disků je 0, není co řešit." << endl;
        return 0;
    }

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy;
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    for (const Tah& tah : tahy) {
        cout << "Přesun disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi);
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