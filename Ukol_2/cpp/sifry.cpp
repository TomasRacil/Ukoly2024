#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru) {
    std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        std::cerr << "Chyba: Soubor nelze otevřít - " << jmeno_souboru << std::endl;
        return "";
    }

    std::string obsah, radek;
    while (getline(soubor, radek)) {
        obsah += radek + "\n";
    }

    soubor.close();
    return obsah;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah) {
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        std::cerr << "Chyba: Soubor nelze otevřít pro zápis - " << jmeno_souboru << std::endl;
        return;
    }

    soubor << obsah;
    soubor.close();
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
    std::string vysledek;
    size_t delkaKlice = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        vysledek += text[i] ^ klic[i % delkaKlice];
    }

    return vysledek;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat) {
    std::string vysledek;
    int skutecnyPosun = sifrovat ? posun : -posun;

    for (char znak : text) {
        if (isalpha(znak)) {
            char zaklad = isupper(znak) ? 'A' : 'a';
            znak = (znak - zaklad + skutecnyPosun + 26) % 26 + zaklad;
        }
        vysledek += znak;
    }

    return vysledek;
}

// Funkce pro Vigenereovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
    std::string vysledek;
    size_t delkaKlice = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        char znak = text[i];
        char klicZnak = klic[i % delkaKlice];
        int posun = sifrovat ? (klicZnak - 'a') : -(klicZnak - 'a');

        if (isalpha(znak)) {
            char zaklad = isupper(znak) ? 'A' : 'a';
            znak = (znak - zaklad + posun + 26) % 26 + zaklad;
        }

        vysledek += znak;
    }

    return vysledek;
}

#ifndef __TEST__ 
int main() {
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");

    // Kontrola nacteni vstupniho souboru
    if (vstupni_text.empty()) {
        return 1;
    }

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Caesar sifra (sifrovany text): " << std::endl << sifrovany_text_caesar << std::endl;

    // Šifrování textu pomocí Vigenereovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << "Vigenere sifra (sifrovany text): " << std::endl << sifrovany_text_vigener << std::endl;

    // Šifrování textu pomocí XOR šifry
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
    std::cout << "XOR sifra (sifrovany text): " << std::endl << sifrovany_text_xor << std::endl;

    // Uložení šifrovaných textů do souborů
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

    // Dešifrování textů
    std::cout << "Desifrovany text pomoci Caesarovy sifry: " 
              << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;

    std::cout << "Desifrovany text pomoci Vigenereovy sifry: " 
              << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;

    std::cout << "Desifrovany text pomoci XOR sifry: " 
              << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

    return 0;
}
#endif // __TEST__