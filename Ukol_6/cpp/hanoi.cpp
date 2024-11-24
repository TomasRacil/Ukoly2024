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

    //added constructor
    Tah(int disk, char z, char na, vector<vector<int>> stavVezi) : disk(disk), z(z), na(na), stavVezi(stavVezi) {};
};


void provedTah(vector<vector<int>> &veze, Tah tah)
{
    // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠶⠶⠶⠶⠶⠶⠶⠶⣶⣶⣶⣶⣶⠶⠶⠶⠶⠶⠶⠶⢶⣤⣤⣤⣄⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    // ⠀⠀⠀⠀⠀⠀⠀⠀⣠⡿⠋⠀⠀⠀⠀⢀⡠⠔⠒⢉⣉⣀⣠⠠⢄⣠⣀⣀⡀⠀⠀⠀⠀⠀⠀⠉⣉⣛⣛⡛⠷⣦⣄⠀⠀⠀⠀⠀⠀⠀
    // ⠀⠀⠀⠀⠀⠀⢀⣼⠏⠀⠀⠀⢀⠴⠊⣡⠔⣚⡩⠥⠤⠤⠔⠦⢤⠄⠀⠀⠈⠉⠉⠉⠉⣉⣉⣉⣀⣀⠀⠉⠀⠈⠙⠻⣦⡀⠀⠀⠀⠀
    // ⠀⠀⠀⠀⠀⢀⣾⠏⠀⠀⠀⠊⢁⡴⢋⠴⠊⠁⠀⠀⠀⠀⠀⠀⠀⢣⠀⠀⠀⠀⠀⠈⢹⠃⠀⠀⠀⠀⠉⠢⡀⠀⠀⠀⠸⣷⠀⠀⠀⠀
    // ⠀⠀⠀⠀⢀⣾⠏⠀⠀⠀⠀⠀⠉⠐⠁⣀⣤⣴⣶⣶⣶⡶⣶⣤⣀⠈⠀⠀⠀⠀⠀⠀⡎⠀⠀⢀⣀⣀⠀⠀⠑⠀⠀⠀⠀⢿⡄⠀⠀⠀
    // ⠀⠀⢀⣴⣿⣷⡤⠄⠀⠀⠀⣤⡔⠀⣾⣿⣽⣿⣿⣿⣿⣤⣄⡉⠻⣷⡆⠀⠀⠀⣀⣀⣤⣶⣿⣿⣿⣿⣿⣷⠄⠤⠤⠤⢤⣈⠻⣶⡀⠀
    // ⠀⣴⢟⡟⠁⢀⣴⡶⠾⠶⣶⣤⣈⡁⠈⠉⠀⣀⣴⡗⠀⠉⠙⠻⢿⠟⠁⠀⠀⠀⠙⢻⣿⠛⠋⠉⠉⠀⠀⠀⠀⢀⣀⣀⠰⢌⠓⢌⢿⡄
    // ⣸⡏⢸⠀⣰⡿⠁⠀⢠⣷⡀⠉⠙⠛⠻⠿⠟⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡀⠀⠀⠀⢶⣤⣤⣾⠟⠛⠛⠿⠆⡇⢘⣾⡇
    // ⣿⡄⢸⠀⣿⡇⣠⣴⣿⡟⠻⢷⣦⣄⡀⠀⠀⠀⣀⣀⣀⡤⢦⣴⡶⠶⠀⠀⠀⠀⠀⠀⠉⠻⣷⣄⠀⠀⠉⠉⠁⢠⣿⡀⠀⢀⠇⢸⣻⡇
    // ⢹⣧⠘⡆⠸⣧⠀⠀⢹⣷⣄⠀⠈⠙⣿⡷⣶⣤⣄⣀⠀⠀⠘⣷⡄⢶⠷⠶⠦⠀⠀⠀⢀⣴⡿⠿⠛⠢⢄⠀⢀⣼⣿⣧⢀⡡⠔⣻⡟⠀
    // ⠀⠹⣷⣌⠓⠬⠀⠀⠈⠻⣿⣷⣦⣄⣿⣧⠀⠈⠉⠛⠻⢷⣶⣮⣥⣄⣀⡀⠀⠀⠹⠷⠟⠋⠀⠀⢀⣀⣤⣷⣿⠿⣿⣿⠀⠀⢰⡿⠁⠀
    // ⠀⠀⠈⠻⣯⡀⠀⠀⠀⠀⠙⣷⡌⠙⣿⣿⣿⣶⣤⣄⡀⣼⡏⠀⠉⠉⠛⢻⣿⠟⠿⠿⣿⡿⠿⠟⠛⣿⡏⠀⣿⡇⣿⣿⠀⠀⣺⡇⠀⠀
    // ⠀⠀⠀⠀⠙⣷⡀⠀⠀⠀⠀⠈⢻⣦⣾⠇⠈⠙⠛⠿⣿⣿⣷⣶⣤⣤⣤⣤⣿⣤⣤⣤⣼⣧⣤⣤⣤⣼⣷⣴⣿⣿⣿⣿⠀⠀⢾⡇⠀⠀
    // ⠀⠀⠀⠀⠀⠘⣷⡄⠀⠀⠀⠀⠀⠙⠻⣦⣄⠀⠀⠀⣸⡏⠉⠙⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⢾⡇⠀⠀
    // ⠀⠀⠀⠀⠀⠀⠈⢿⣦⡀⠀⡀⠀⠀⠀⠈⠛⢷⣦⣠⣿⠁⠀⠀⠀⠀⢈⣿⠀⠉⠉⢉⣿⠛⠛⢻⡿⠋⣹⡟⢹⣿⣾⠇⠀⠀⣺⡇⠀⠀
    // ⠀⠀⠀⠀⠀⠀⠀⠀⠘⠻⣦⣉⠓⠤⣉⠒⠤⣀⠈⠙⠻⠷⢶⣤⣤⣄⣸⣿⣀⣀⣀⣸⣟⣀⣠⣿⣇⣴⣿⣶⡾⠟⠁⠀⠀⠀⢼⡇⠀⠀
    // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⣦⣌⡉⠲⠤⣉⠒⠦⢄⣀⠀⠈⠉⠉⠉⠉⠉⠉⠋⠉⠉⠉⠉⠉⠉⠀⠀⠀⡠⠀⠀⡀⠀⢸⡇⠀⠀
    // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⠷⣦⣄⡉⠑⠒⠬⠭⣖⣒⡤⠤⠤⠤⠤⠤⠤⠤⣀⢄⡠⠤⠤⠒⠉⠀⢀⡰⠃⠀⢸⡇⠀⠀
    // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠷⣶⣤⣀⠀⠀⠈⠉⠉⠒⠒⠒⠒⠐⠠⠦⠴⠤⠴⠤⠴⠒⠉⠀⠀⠀⣼⡇⠀⠀
    // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⣶⣦⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⠏⠀⠀⠀
    // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠛⠻⠷⠶⢶⣦⣤⣤⣤⣤⣤⡴⠶⠟⠋⠁⠀⠀⠀⠀
}


// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    //break the recursion, take care of invalid n
    if (n <= 0) {
        return;
    }

    //init towers when they're empty, even though n is valid
    if (veze[0].empty() && veze[1].empty() && veze[2].empty())
        for (int i=n;i>0;--i)
            veze[0].push_back(i);

    //transfer disc from start to auxiliary via end
    hanoi(n-1, z      ,cil  ,pomocny,veze,tahy);


    //move disc from z tower to cil tower in veze vector
    //no need for provedTah, this is just faster
    //subtracting 'A from char representing the tower A,B,C results in correct indexing of vector without the need of extra variables
    veze[cil - 'A'].push_back(veze[z - 'A'].back());
    veze[z - 'A'].pop_back();

    //store current step in tahy vector
    tahy.push_back(Tah(n,z,cil,veze));

    //transfer disc from auxiliary to end via start
    hanoi(n-1, pomocny,z    ,cil    ,veze,tahy);
}

void zobrazVeze(vector<vector<int>> &veze)
{
    //cannot print towers when there are no towers
    if (veze.empty()) {
        return;
    }

    //get total number of discs
    int discs_cnt = veze[0].size() + veze[1].size() + veze[2].size();

    //print towers from top to bottom
    //the widest tower is discs_cnt*2 + 1 wide
    //all towers are discs_cnt + 1 high

    //spaces before and after empty tower piece calculated according to widest tower
    string spaces;
    for (int i=0;i<discs_cnt+1;++i)
        spaces += ' ';

    //for all rows:
    for (int i = discs_cnt;i>=0;--i) {

        //for all columns (towers):
        for(int j=0;j<3;++j) {

            //print disc if there is any on current row:
            if (veze[j].size() > i) {

                //print spaces before the disc depending on disc width
                cout << spaces.substr(0,discs_cnt - veze[j][i] + 1);
                //print disc
                for (int k = 0;k<veze[j][i]*2+1;++k)
                    cout << "=";
                //print spaces after the disc
                cout << spaces.substr(0,discs_cnt - veze[j][i] + 1);
            }
            //print empty tower piece
            else {
                cout << spaces << "|" << spaces;
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