#include <iostream>
#include <vector>
#include <iomanip> 
#include <string>  

using namespace std;

struct Tah 
{
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; 
};

void provedTah(vector<vector<int>>& veze, Tah& tah) 
{
    if (veze[tah.z - 'A'].empty()) 
    {
        cerr << "Chyba: Snažíte se odebrat disk z prázdné věže." << endl;
        return;
    }

    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);
    tah.stavVezi = veze;
}

void zobrazVeze(const vector<vector<int>>& veze) 
{
    int maxHeight = 0;
    for (const auto& vez : veze) 
    {
        maxHeight = max(maxHeight, static_cast<int>(vez.size()));
    }

    for (int i = maxHeight - 1; i >= 0; --i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            if (i < veze[j].size()) 
            {
                int disk = veze[j][i];
                string diskViz = string(disk * 2, '='); 
                int padding = (maxHeight * 2 - disk * 2) / 2; 
                cout << setw(padding + diskViz.length()) << diskViz << setw(padding) << " ";
            }
            else 
            {
                string emptySpace(maxHeight * 2, ' '); 
                cout << setw(emptySpace.length()) << "|" << setw(1) << " ";
            }
        }
        cout << endl;
    }
    cout << string(maxHeight * 2, '-') << "   "
        << string(maxHeight * 2, '-') << "   "
        << string(maxHeight * 2, '-') << endl;
    cout << "   A           B           C   " << endl << endl;
}

void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy) 
{
    if (n <= 0) 
    {
        return; 
    }
    if (n == 1) 
    {
        Tah tah = { 1, z, cil, {} };
        provedTah(veze, tah);
        tahy.push_back(tah);
    }
    else 
    {
        hanoi(n - 1, z, cil, pomocny, veze, tahy);

        Tah tah = { n, z, cil, {} };
        provedTah(veze, tah);
        tahy.push_back(tah);

        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

#ifndef __TEST__
int main() 
{
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;

    if (n < 0) 
    {
        cerr << "Chyba: Počet disků nemůže být záporný." << endl;
        return 1;
    }

    vector<vector<int>> veze(3); 
    for (int i = n; i > 0; i--) 
    {
        veze[0].push_back(i); 
    }

    vector<Tah> tahy; 
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    
    for (const Tah& tah : tahy) 
    {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); 
    }

    return 0;
}
#endif // __TEST__