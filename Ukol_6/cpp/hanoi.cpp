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
};

void zobrazVeze(vector<vector<int>> &veze)
{
    int vyska=0;
    for (vector<int> vez:veze)
    {
            vyska+=vez.size();
    }
    vyska++;
    for (int i = vyska;i>0;i--)
    {
        for (vector<int> vez:veze)
        {
            if (vez.size()<i)
            {
                for (int j=vyska-1;j>0;j--)
                    cout << " ";
                cout << "|";
                for (int j=vyska-1;j>0;j--)
                    cout << " ";
                cout << " ";
            }
            else
            {
                int disk;
                disk = vez[i-1]*2-1;
                int prostor = (vyska)*2-1;
                for (int j = (prostor-disk)/2;j>0;j--)
                    cout << " ";
                for (int j = disk;j>0;j--)
                    cout << "=";
                for (int j = (prostor-disk)/2;j>0;j--)
                    cout << " ";
                cout << " ";
            }
        }
        cout << endl;
    }
}
// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah)
{
    int vs;
    switch(tah.z)
    {
        case 'A':
            vs = 0;
            break;
        case 'B':
            vs = 1;
            break;
        case 'C':
            vs = 2;
            break;
    }
    int vc;
    switch(tah.na)
    {
        case 'A':
            vc = 0;
            break;
        case 'B':
            vc = 1;
            break;
        case 'C':
            vc = 2;
            break;
    }
    veze[vs].pop_back();
    veze[vc].push_back(tah.disk);
    tah.stavVezi = veze;
    // for (vector<int> vez:tah.stavVezi)
    // {
    //     for (int i = vez.size()-1;i>=0;i--)
    //     {
    //         cout << vez[i];
    //         cout << " ";
    //     }
    //     cout << endl;
    // }
    zobrazVeze(veze);
    

}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy)
{
    vector<Tah> mensi;
    if (n>0){
        Tah* t = new Tah();
        t->disk = n;
        t->z = z;
        t->na = cil;
        tahy.push_back(*t);
        hanoi(n-1,z,cil,pomocny,veze,mensi);
        tahy.insert(tahy.begin(),mensi.begin(),mensi.end());
        mensi.clear();
        hanoi(n-1,pomocny,z,cil,veze,mensi);
        tahy.insert(tahy.end(),mensi.begin(),mensi.end());
    }
    else
    {
        tahy.clear();
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
        provedTah(veze,tah);
        // zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__