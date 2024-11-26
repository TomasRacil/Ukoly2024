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

// Funkce pro provedení tahu
void provedTah(vector<vector<int>>& veze, Tah tah)
{
	int disk = veze[tah.z - 'A'].back(); // Vyjme disk z počátečního kolíku
	veze[tah.z - 'A'].pop_back(); 
	veze[tah.na - 'A'].push_back(disk); // Vloží disk na cílový kolík
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy)
{
    if (n == 1)
    {
		Tah tah = { n, z, cil, veze }; // Vytvoření tahu
		provedTah(veze, tah); 
		tah.stavVezi = veze; // Uložení stavu věží po provedení tahu
		tahy.push_back(tah); // Uložení tahu do vektoru tahů
    }
    else
    {
		hanoi(n - 1, z, cil, pomocny, veze, tahy); // Rekurzivní volání pro přesunutí n-1 disků na pomocný kolík
		Tah tah = { n, z, cil, veze }; 
        provedTah(veze, tah);
		tah.stavVezi = veze;   // Uložení stavu věží po provedení tahu
        tahy.push_back(tah);
        hanoi(n - 1, pomocny, z, cil, veze, tahy);
    }
}

void zobrazVeze(vector<vector<int>>& veze)
{
	for (int i = 0; i < 3; i++) // Pro každý kolík vypíše jeho obsah 
    {
		cout << "Kolík " << char('A' + i) << ": "; // Výpis kolíku
		for (int disk : veze[i]) // Výpis disků na kolíku
        {
            cout << disk << " ";
        }
        cout << endl;
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
