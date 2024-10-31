
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int soucet; 
int soucin = 1;
double prumer;
double vysledek;
vector<int>cisla;
int cislo;
int scitani(vector<int>cisla);
int nasobeni(vector<int>cisla);
double prumernaHodnota(vector<int>cisla);
double median(vector<int>cisla);

int main()
{
	cout << "Zadejte libovolny pocet cisel (pro ukonceni stisknete cislo 0)";

	while (true) {
		cin >> cislo;
		if (cislo == 0) {
			break;
		}
		cisla.push_back(cislo);
	}
	
	scitani(cisla);
	cout << "Soucet cisel je: " << soucet << endl;
	nasobeni(cisla);
	cout << "Soucin cisel je: " << soucin << endl;
	prumernaHodnota(cisla);
	cout << "Prumerna hodnota je: " << prumer << endl;
	median(cisla);
	cout << "Median je: " << vysledek << endl;
}

int scitani(vector<int>cisla){
	for (size_t i = 0; i < cisla.size(); i++) {
		soucet += cisla[i];
	}
	return soucet;
	
}

int nasobeni(vector<int>cisla) {
	for (size_t j = 0 ; j < cisla.size(); j++) {
		soucin *= cisla[j];
	}
	return soucin;
}

double prumernaHodnota(vector<int>cisla) {
		prumer = static_cast<double>(soucet) / cisla.size();
		return prumer;
}

double median(vector<int>cisla) {
	sort(cisla.begin(), cisla.end());
	size_t velikost = cisla.size();
	
	if (velikost % 2 == 0) {
		 vysledek = (cisla[velikost / 2 - 1] + cisla[velikost / 2]) / 2.0;
		 return vysledek;
	}
	else {
		vysledek = cisla[velikost / 2];
		return vysledek;
	}
}
 