#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
int* nPointer;

// Struktura pro reprezentaci tahu
struct Tah
{
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah)
{
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    if (n == 1) {
        Tah tah = {veze[z - 'A'].back(), z, cil, veze};
        provedTah(veze, tah);
        tah.stavVezi = veze;
        tahy.push_back(tah);
    } else {
        hanoi(n - 1, z, cil, pomocny, veze, tahy);
        Tah tah = {veze[z - 'A'].back(), z, cil, veze};
        provedTah(veze, tah);
        tah.stavVezi = veze;
        tahy.push_back(tah);
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

void zobrazVeze(vector<vector<int>> &veze)
{
    int n = *nPointer;
    int maxDisk = n;

    for (int i = n - 1; i >= 0; i--) {  
        for (int j = 0; j < 3; j++) {
            if (i < veze[j].size()) {
                int disk = veze[j][i];
                int mezery = maxDisk - disk;
                cout << string(mezery, ' ') << string(disk, '=') << "|" << string(disk, '=') << string(mezery, ' ');
            } else {
                cout << string(maxDisk, ' ') << "|" << string(maxDisk, ' ');
            }
            cout << "   ";
        }
        cout << endl;
    }
    
    cout << string(maxDisk - 1, ' ') << "A" << string(maxDisk * 2 + 3, ' ') << "B" << string(maxDisk * 2 + 3, ' ') << "C" << endl;
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; 
}

#ifndef __TEST__
int main()
{
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    nPointer = &n;

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (Tah tah : tahy)
    {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); 
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        clearScreen();
    }

    return 0;
}
#endif // __TEST__

/*
cd Ukol_3/cpp
make build
cd build 

cmake ..
make
./mytests
*/

/*
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
*/
