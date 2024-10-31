#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Funkce pro otevření souboru
string otevri_soubor(const string& jmeno_souboru)
{
	string radek;
	ifstream soubor(jmeno_souboru, ios::binary);
	if (!soubor.is_open())
	{
		// Chyba při otevírání souboru
		cerr << "Chyba pri otevirani souboru: " << jmeno_souboru << endl;

		return "";
	}
	
	char ch;
	// Čteme soubor znak po znaku
	while (!soubor.eof() ){
		soubor.get(ch);
		 radek += ch; 
			cout << ch; 
	}
		soubor.close();
	

	// Implementace funkce pro otevření souboru a načtení jeho obsahu
	return radek;
}

// Funkce pro Caesarovu šifru
string caesar_sifra(const string& text, int posun, bool sifrovat)
{
	// sifrovat = true pro šifrování, sifrovat = false pro dešifrování
	if (sifrovat == false) {
		// změna z šifrování na nešifrování
		posun = ( - posun);
	}
	int i;
	char a;
	string vysledek = text;
	for (i = 0; i < text.length(); i++) {
		if (isalpha(text[i])) {
			char baze = islower(vysledek[i]) ? 'a' : 'A';
			// Posun znaku a zajištění cyklického posunu
			vysledek[i] = (vysledek[i] - baze + posun + 26) % 26 + baze;
		}
	}
	// Implementace Caesarovy šifry
	
	return vysledek;
}

// Funkce pro Vigenerovu šifru
string vigener_sifra(const string& text, const string& klic, bool sifrovat)
{
	
	string vysledek = text;
	int delka_klice = klic.length();
	int index_klice = 0;

	for (char& znak : vysledek) {
		if (isalpha(znak)) {
			char baze = islower(znak) ? 'a' : 'A';
			int posun = (islower(klic[index_klice]) ? klic[index_klice] - 97 : klic[index_klice] - 65);
			if (!sifrovat) {
				// Opačný posun pro dešifrování
				posun = -posun;
			}
			znak = (znak - baze + posun + 26) % 26 + baze;
			index_klice = (index_klice + 1) % delka_klice;
		}
	}

	return vysledek;
	
}

// Funkce pro XOR šifru
string xor_sifra(const string& text, const string& klic, bool sifrovat)
{
	string vysledek = text;
	for (int i = 0; i < text.length(); i++) {
		vysledek[i] =char( text[i] ^ klic[i % klic.length()]);
	}
	// Implementace XOR šifry
	
	return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string& jmeno_souboru, const std::string& obsah)
{
	fstream soubor;
	soubor.open(jmeno_souboru, ios::out);
	if (soubor.is_open()) {
		soubor << obsah << endl;
		soubor.close();
	}
	printf("ulozeno\n");
	// Implementace funkce pro uložení řetězce do souboru
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
	// Načtení vstupního souboru
	string vstupni_text = otevri_soubor("vstup.txt");
	printf("\n");

	// Šifrování textu pomocí Caesarovy šifry
	string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
	cout << sifrovany_text_caesar << endl;
	

	// Šifrování textu pomocí Vigenerovy šifry
	string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
	cout << sifrovany_text_vigener << endl;
	
	
	// Šifrování textu pomocí XOR šifry
	string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
	cout << sifrovany_text_xor << endl;
	

	
	// Uložení šifrovaných textů do souborů
	uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
	uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
	uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

	
	// Dešifrování textů
	
	
	cout << "Dešifrovany text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
	cout << "Dešifrovany text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
	cout << "desifrovana zprava xor " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false);

	return 0;
}
#endif // __TEST__
