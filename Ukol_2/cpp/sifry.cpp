#include <iostream>
#include <fstream>
#include <string>


// Funkce pro otevření souboru
std::string otevri_soubor(const std::string& jmeno_souboru) {
    std::ifstream soubor(jmeno_souboru);

    if (!soubor.is_open()) {
        std::cerr << "Chyba: Soubor " << jmeno_souboru << " nelze otevřít." << std::endl;
        return "";
    }

    std::string obsah;
    std::string radek;
    while (std::getline(soubor, radek)) {
        obsah += radek + '\n';
    }

    if (!soubor.eof()) {
        std::cerr << "Chyba při čtení souboru: " << jmeno_souboru << std::endl;
        return "";
    }
    return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
  // Implementace Caesarovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
    std::string vysledek; 
    for (char znak : text) {  // Provede pro každý char v souboru
        if (isalpha(znak)) {  // Zkontroluje jestli je char z abecedy
            char zacatek = islower(znak) ? 'a' : 'A'; // Rozlišuje jestli je char malé nebo velké písmeno
            int index = znak - zacatek;
            if (sifrovat == true) {    // zkontrolovat
                index = (index + posun + 26) % 26;  // šifrování 
            } else {
                index = (index - posun + 26) % 26;  // dešifrování
            }
          vysledek += zacatek + index;
        } 
        else if (isspace(znak)) { // Pokud je znak mezera
          vysledek += znak;
        }
        else {
          vysledek += znak;
        }
    }
    return vysledek;
}


// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
    std::string vysledek;
    int j = 0;
    for (char znak : text) {  // Provede pro každý char v souboru podle klice
        if (isalpha(znak)) {  // Zkontroluje jestli je char z abecedy
            char zacatek = islower(znak) ? 'a' : 'A'; // Rozlišuje jestli je char malé nebo velké písmeno
            int index = znak - zacatek;
            int klic_index = tolower(klic[j % klic.length()]) - 'a';
            if (sifrovat == true) {
                index = (index + klic_index + 26) % 26;   // šifrování
            } else {
                index = (index - klic_index + 26) % 26;   // dešifrování
            }
            vysledek += zacatek + index;
            j++;    // Posune se na další char v klíči
        } 
        else {
            vysledek += znak;
        }
    }
    return vysledek;
  // Implementace Vigenerovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  return "";
}


// Funkce pro XOR šifru

  // Implementace XOR šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování

std::string xor_sifra(const std::string& text, const std::string& klic, bool sifrovat) {
    std::string vysledek;
    size_t indexKlice = 0;

    for (char znak : text) {
        // XOR operace na jednotlivých bitech znaků
        char zašifrovaný_znak = znak ^ klic[indexKlice % klic.size()];
        vysledek += zašifrovaný_znak;

        // Zvýšení indexu klíče
        indexKlice++;
    }

    return vysledek;
}


// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah) {
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {    // Kontroluje že je soubor stále otevřený pokud ne došlo k chybě
        std::cerr << "Chyba při ulkádaní souboru: " << jmeno_souboru << std::endl;
        return;
    }
    soubor << obsah;    // Nahraje obsah do souboru
    soubor.close();     // Uzavře soubor
}


#ifndef _TEST_
int main()
{
	// Načtení vstupního souboru
	std::string vstupni_text = otevri_soubor("vstup.txt");

	// Šifrování textu pomocí Caesarovy šifry
	std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
	std::cout << sifrovany_text_caesar << std::endl;

	// Šifrování textu pomocí Vigenerovy šifry
	std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
	std::cout << sifrovany_text_vigener << std::endl;

	// Šifrování textu pomocí XOR šifry
	std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
	std::cout << sifrovany_text_xor << std::endl;

	// Uložení šifrovaných textů do souborů
	uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
	uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
	uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

	// Dešifrování textů
	std::cout << "Dešifrovany text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
	std::cout << "Dešifrovany text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
	std::cout << "Dešifrovany text pomocí XOR šifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

	return 0;
}
#endif // _TEST_


// komentař kvůli uložení