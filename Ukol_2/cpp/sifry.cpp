#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Funkce pro otevření souboru
string otevri_soubor(const string& jmeno_souboru)
{
	// Implementace funkce pro otevření souboru
	ifstream vstupni_soubor(jmeno_souboru, ios::binary);
	if (!vstupni_soubor)
	{
		cout << "Nemohu otevřít soubor: " << jmeno_souboru << endl;
		return "";
	}
	string obsah, radek;
	/* delalo mi to chybu u XOR sifry z nejakeho duvodu mi to vypisovalo y na konci desifrace
	while (getline(vstupni_soubor, radek)) 
		obsah += radek + "\n";
	}
	*/
	obsah = string((istreambuf_iterator<char>(vstupni_soubor)), istreambuf_iterator<char>());
	return obsah;

}

// Funkce pro Caesarovu šifru
string caesar_sifra(const string& text, int posun, bool sifrovat)
{
	// Implementace Caesarovy šifry
	// sifrovat = true pro šifrování, sifrovat = false pro dešifrování
	string vysledek = "";
	vysledek = text;

	for (char& znak : vysledek)
	{
		if (isalpha(znak))
		{
			char zaklad = islower(znak) ? 'a' : 'A';
			znak = zaklad + (znak - zaklad + (sifrovat ? posun : 26 - posun)) % 26;
		}
	}
	return vysledek;
}

// Funkce pro Vigenerovu šifru
string vigener_sifra(const string& text, const string& klic, bool sifrovat)
{
	// Implementace Vigenerovy šifry
	// sifrovat = true pro šifrování, sifrovat = false pro dešifrování
	string vysledek = text;
	int klicIndex = 0;
	int klicDelka = klic.length();

	for (char& znak : vysledek)
	{
		if (isalpha(znak))
		{
			char zaklad = islower(znak) ? 'a' : 'A';
			char k = islower(klic[klicIndex]) ? (klic[klicIndex] - 'a') : (klic[klicIndex] - 'A');
			znak = zaklad + (znak - zaklad + (sifrovat ? k : 26 - k)) % 26;
			klicIndex = (klicIndex + 1) % klicDelka;
		}
	}
	return vysledek;
}

// Funkce pro XOR šifru
string xor_sifra(const string& text, const string& klic, bool sifrovat)
{
	// Implementace XOR šifry
	// sifrovat = true pro šifrování, sifrovat = false pro dešifrování
	string vysledek = text;
	string a, b, c;
	for (int i = 0; i < text.length(); ++i)
	{
		vysledek[i] = text[i] ^ klic[i % klic.length()];
	}
	return vysledek;
}
void uloz_do_souboru(const string& jmeno_souboru, const string& obsah)
{
	// Implementace funkce pro uložení řetězce do souboru
	ofstream vystupni_soubor(jmeno_souboru, ios::binary);
	if (!vystupni_soubor)
	{
		cout << "Nemohu otevrit soubor: " << jmeno_souboru << endl;
		return;
	}
	vystupni_soubor << obsah;
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
	// Načtení vstupního souboru
	string vstupni_text = otevri_soubor("vstup.txt");

	//kontrola zda je soubor prazdny nebo zda existuje
	if (vstupni_text.empty())
	{
		cout << "Soubor je prazdny nebo neexistuje." << endl;
	}
	else
	{
		cout << "Nacteny text: " << vstupni_text << endl;
	}

	// Šifrování textu pomocí Caesarovy šifry
	string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
	cout << "Ceaser sifra: " << sifrovany_text_caesar << endl;

	// Šifrování textu pomocí Vigenerovy šifry
	string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
	cout << "Vigener sifra: " << sifrovany_text_vigener << endl;

	// Šifrování textu pomocí XOR šifry
	string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
	//cout << "len: " << vstupni_text.size() << endl; hledal jsem chybu
	cout << "Xor sifra: " << sifrovany_text_xor << endl;
	//cout << "Xor sifra len: " << sifrovany_text_xor.size() << endl; hledal jsem chybu

	// Uložení šifrovaných textů do souborů
	uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
	uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
	uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

	// Dešifrování textů
	cout << "\nDesifrovany text pomoci Caesarovy sifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << endl;
	cout << "Desifrovany text pomoci Vigenerovy sifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << endl;
	cout << "Desifrovany text pomoci XOR sifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << endl;

	return 0;
}
#endif // __TEST__
