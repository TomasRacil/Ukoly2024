#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int> > stavVezi;
};


void provedTah(vector<vector<int> >& veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);

}


void hanoi(int n, char z, char pomocny, char cil, vector<vector<int> >& veze, vector<Tah>& tahy) {
    if (n <= 0) {
        return;
    }
    if (veze[0].empty() && veze[1].empty() && veze[2].empty())
        for (int i=n;i>0;--i)
            veze[0].push_back(i);
    if (n == 1) {
        Tah tah = {n, z, cil, veze};
        tahy.push_back(tah);
        provedTah(veze, tah);
        tah.stavVezi = veze;
        
    } else {
        hanoi(n - 1, z, cil, pomocny, veze, tahy);
        Tah tah = {n, z, cil, veze};
        tahy.push_back(tah);
        provedTah(veze, tah);
        tah.stavVezi = veze;
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
            }
    
}


void zobrazVeze(const vector<vector<int> >& veze,int vyska) {
int totalWidth = vyska * 2 +1; // sirka vezi

    for (int i = vyska - 1; i >= 0; --i) {
        for (int j = 0; j < 3; ++j) {
            if (i < veze[j].size()) {
                int disk = veze[j][i];
                int diskWidth = disk * 2+1;
                int padding = (totalWidth - diskWidth) / 2; // Pocet mezer pred a za diskem
                cout << string(padding, ' ') << string(diskWidth, '=') << string(padding, ' ');
            } else {
                cout << string(totalWidth / 2, ' ') << "|" << string(totalWidth / 2, ' ');
            }
            cout << "   "; // mezera mezi vezemi
        }
        cout << endl;
    }

    // zakladna vezi
    for (int j = 0; j < 3; ++j) {
        cout << string(totalWidth, '-') << "   ";
    }
    cout << endl;
}

#ifndef __TEST__
int main()
{
    int n;
    string mezi;
    cout << "Zadejte pocet disku: ";
    cin >> mezi;
    if (mezi.find_first_not_of("0123456789") != string::npos) {
        cout << "Nespravny vstup." << endl;
        return 0;
    }
    else {
        n = stoi(mezi);
    }
    cin.ignore();

    vector<vector<int> > veze(3);
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    //tyhle dva radky jsem vytvarel hodinu
    Tah tah = {0, 'A', 'A', veze}; // Počáteční stav věží
    tahy.push_back(tah); // Uložení počátečního stavu věží
    hanoi(n, 'A', 'B', 'C', veze, tahy);
    
    // Zobrazení tahů a stavů věží
    for (Tah tah: tahy)
    {   
        provedTah(tah.stavVezi, tah); // Provedení tahu
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi,n); // Zobrazení stavu věží po tahu
    }
    return 0;
}
#endif // __TEST__