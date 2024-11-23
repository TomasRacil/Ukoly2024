#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah
{
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu

    //constructor
    Tah(int disk, char z, char na, vector<vector<int>> stavVezi) : disk(disk), z(z), na(na), stavVezi(stavVezi) {};
};

// Funkce pro provedení tahu (?? pointless)
void provedTah(vector<vector<int>> &veze, Tah tah)
{
    //provede presunuti mensiho disku na vetsi smerem doprava
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    if (n <= 0) {
        return;
    }

    //transfer disc from start to auxiliary via end
    hanoi(n-1, z      ,cil  ,pomocny,veze,tahy);

    //move disc from z tower to cil tower
    int from_idx;
    switch(z) {
        case 'A':
            from_idx = 0;
            break;
        case 'B':
            from_idx = 1;
            break;
        case 'C':
            from_idx = 2;
            break;
    }
    int to_idx;
    switch(cil) {
        case 'A':
            to_idx = 0;
            break;
        case 'B':
            to_idx = 1;
            break;
        case 'C':
            to_idx = 2;
            break;
    }
    veze[to_idx].push_back(veze[from_idx].back());
    veze[from_idx].pop_back();

    //push back current state of discs and operation to tahy
    tahy.push_back(Tah(n,z,cil,veze));

    //transfer disc from auxiliary to end via start
    hanoi(n-1, pomocny,z    ,cil    ,veze,tahy);
}

void zobrazVeze(vector<vector<int>> &veze)
{
    if (veze.empty()) {
        //cannot print towers when there are no towers
        return;
    }

    //get number of discs:
    int discs_cnt = veze[0].size() + veze[1].size() + veze[2].size();

    //print towers from top to bottom
    //the widest tower is discs_cnt*2 + 1 wide
    //all towers are discs_cnt + 1 high

    //for all rows:
    for (int i = discs_cnt;i>=0;--i) {
        //for all columns (towers):
        for(int j=0;j<3;++j) {
            //print disc if there is any on current row:
            if (veze[j].size() > i) {
                //spaces_cnt are spaces needed before and after the disc, depending on disc's width
                int spaces_cnt = discs_cnt - veze[j][i] + 1;
                //print spaces before disc:
                for (int k=0;k<spaces_cnt;++k)
                    cout << " ";
                //print disc
                for (int k = 0;k<veze[j][i]*2+1;++k)
                    cout << "=";
                //print spaces after disc:
                for (int k=0;k<spaces_cnt;++k)
                    cout << " ";
            }
            //print empty spot
            else {
                //print spaces before '|'
                for(int k=0;k<discs_cnt+1;++k)
                    cout << " ";
                cout << "|";
                //print spaces after '|'
                for(int k=0;k<discs_cnt+1;++k)
                    cout << " ";
            }
        }
        cout << "\n";
    }


}

#ifndef __TEST__
int main()
{
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();


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
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__