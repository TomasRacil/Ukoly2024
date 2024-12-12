#include <iostream>     //znovu
#include <fstream>
#include <string>
#include <cctype> 

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string& jmeno_souboru)
{
	// Implementace funkce pro otevření souboru a načtení jeho obsahu
	std::ifstream soubor(jmeno_souboru); 
	if (!soubor.is_open()) { 
		std::cerr << "Chyba: Soubor " << jmeno_souboru << " nelze otevřít." << std::endl;
		return ""; 
	}

	std::string obsah;
	std::string radek;
	while (std::getline(soubor, radek)) {
		obsah += radek; 
	}

	soubor.close(); 
	return obsah;
}

    return obsah;
}
// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string& text, int posun, bool sifrovat)
{
	std::string vysledek = "";
	int realny_posun = posun;

	if (!sifrovat) {
		realny_posun = -posun;
	}

	for (char znak : text) {
		if (isalpha(znak)) { 
			char zaklad = islower(znak) ? 'a' : 'A'; 
			znak = (znak - zaklad + realny_posun + 26) % 26 + zaklad;
		}
		vysledek += znak;
	}
	return vysledek;
}


        if (isalpha(c)) 
        { 
            char offset = isupper(c) ? 'A' : 'a';  
            if (sifrovat) 
            {
                // Šifrování
                c = (char)(((c - offset + posun) % 26 + 26) % 26 + offset);
            } else 
            {
                // Dešifrování
                c = (char)(((c - offset - posun + 26) % 26 + 26) % 26 + offset);
            }
        }
    }
    return vysledek;
}
// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
	std::string vysledek = "";
	int delka_klice = klic.length();
	int posun;

	for (size_t i = 0; i < text.length(); ++i) {
		char znak = text[i];

		if (isalpha(znak)) {
			char znak_klice = klic[i % delka_klice];
			posun = tolower(znak_klice) - 'a'; 

			if (!sifrovat) {
				posun = -posun; 
			}

			if (islower(znak)) {
				znak = (znak - 'a' + posun + 26) % 26 + 'a';
			}
			else if (isupper(znak)) {
				znak = (znak - 'A' + posun + 26) % 26 + 'A';
			}
		}

		vysledek += znak;
	}

	return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string& text, const std::string& klic, bool /*sifrovat*/)
{
	std::string vysledek = "";
	int delka_klice = klic.length();

	for (size_t i = 0; i < text.length(); ++i) {
		char znak_klice = klic[i % delka_klice];
		vysledek += text[i] ^ znak_klice;
	}

	return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string& jmeno_souboru, const std::string& obsah)
{
	std::ofstream soubor(jmeno_souboru);

	if (!soubor.is_open()) {
		std::cerr << "Chyba: Soubor " << jmeno_souboru << " nelze otevřít." << std::endl;
		return;
	}

	soubor << obsah;
	soubor.close();

	std::cout << "Obsah byl úspěšně uložen do souboru: " << jmeno_souboru << std::endl;
}

// Hlavní funkce, která se spustí pouze, pokud není definováno makro __TEST__
#ifndef __TEST__
int main()
{
	std::string vstupni_text = otevri_soubor("vstup.txt");

	std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
	std::cout << sifrovany_text_caesar << std::endl;

	std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
	std::cout << sifrovany_text_vigener << std::endl;

	std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
	std::cout << sifrovany_text_xor << std::endl;

	uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
	uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
	uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

	std::cout << "Dešifrovany text pomocí Caesarovy šifry: " 
              << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
	std::cout << "Dešifrovany text pomocí Vigenerovy šifry: " 
              << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
	std::cout << "Dešifrovany text pomocí XOR šifry: " 
              << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

	return 0;
}
#endif // __TEST__

