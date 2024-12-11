#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
// Funkce pro otevření souboru
std::string otevri_soubor(const std::string& jmeno_souboru)
{
    std::ifstream vstupniSoubor(jmeno_souboru, std::ios::binary);
    if (!vstupniSoubor.is_open()) {
        std::cerr << "Nelze otevřít soubor: " << jmeno_souboru << std::endl;
        return "";
    }

    std::string obsah((std::istreambuf_iterator<char>(vstupniSoubor)), std::istreambuf_iterator<char>());
    vstupniSoubor.close();
    return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string& text, int posun, bool sifrovat)
{
    std::string vysledek = text;
    for (char& c : vysledek) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            char zaklad = std::islower(static_cast<unsigned char>(c)) ? 'a' : 'A';
            if (sifrovat) {
                c = (c - zaklad + posun) % 26 + zaklad;
            }
            else {
                c = (c - zaklad - posun + 26) % 26 + zaklad;
            }
        }
    }
    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
    std::string vysledek = text;
    size_t delkaKlice = klic.length();
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        char k = klic[i % delkaKlice];
        if (std::isalpha(static_cast<unsigned char>(c))) {
            char zaklad = std::islower(static_cast<unsigned char>(c)) ? 'a' : 'A';
            char zakladKlic = std::islower(static_cast<unsigned char>(k)) ? 'a' : 'A';
            if (sifrovat) {
                c = (c - zaklad + (k - zakladKlic)) % 26 + zaklad;
            }
            else {
                c = (c - zaklad - (k - zakladKlic) + 26) % 26 + zaklad;
            }
        }
        vysledek[i] = c;
    }
    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
    std::string vysledek = text;
    size_t delkaKlice = klic.length();
    for (size_t i = 0; i < text.length(); ++i) {
        vysledek[i] = text[i] ^ klic[i % delkaKlice];
    }
    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string& jmeno_souboru, const std::string& obsah)
{
    std::ofstream vystupniSoubor(jmeno_souboru, std::ios::binary);
    if (!vystupniSoubor.is_open()) {
        std::cerr << "Nelze otevřít soubor: " << jmeno_souboru << std::endl;
        return;
    }
    vystupniSoubor << obsah;
    vystupniSoubor.close();
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");
    if (vstupni_text.empty()) {
        std::cerr << "Vstupní soubor je prázdný nebo nebyl načten." << std::endl;
        return 1;
    }

    std::cout << "Vstupní text: " << vstupni_text << std::endl;

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Caesarova šifra: " << sifrovany_text_caesar << std::endl;

    // Šifrování textu pomocí Vigenerovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << "Vigenerova šifra: " << sifrovany_text_vigener << std::endl;

    // Šifrování textu pomocí XOR šifry
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
    std::cout << "XOR šifra: " << sifrovany_text_xor << std::endl;

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
#endif // __TEST_
