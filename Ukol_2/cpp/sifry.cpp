#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string& vstup)
{
    std::ifstream soubor(vstup);
    if (!soubor.is_open()) {
        std::cerr << "Nepodařilo se otevřít soubor: " << vstup << std::endl;
        return "";
    }

    std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
   // soubor.close();
    return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string& text, int posun, bool sifrovat)
{
    std::string vysledek = "";
    int real_posun = sifrovat ? posun : -posun;

    for (char znak : text) {
        if (isalpha(znak)) {
            char zaklad = islower(znak) ? 'a' : 'A';
            znak = zaklad + (znak - zaklad + real_posun + 26) % 26;
        }
        vysledek += znak;
    }

    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
    std::string vysledek = "";
    int klic_delka = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        char znak = text[i];
        char klic_znak = klic[i % klic_delka];

        if (isalpha(znak)) {
            char zaklad = islower(znak) ? 'a' : 'A';
            char zaklad_klic = islower(klic_znak) ? 'a' : 'A';
            int posun = sifrovat ? (klic_znak - zaklad_klic) : -(klic_znak - zaklad_klic);
            znak = zaklad + (znak - zaklad + posun + 26) % 26;
        }

        vysledek += znak;
    }

    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
    std::string vysledek = "";
    int klic_delka = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        vysledek += text[i] ^ klic[i % klic_delka];
    }

    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string& jmeno_souboru, const std::string& obsah)
{
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        std::cerr << "Nepodařilo se uložit do souboru: " << jmeno_souboru << std::endl;
        return;
    }

    soubor << obsah;
    soubor.close();
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");

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
    std::cout << "Dešifrovaný text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
    std::cout << "Dešifrovaný text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
    std::cout << "Dešifrovaný text pomocí XOR šifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

    return 0;
}
#endif // __TEST__
