#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open())
    {
        std::cerr << "Soubor " << jmeno_souboru << " nebyl nalezen." << std::endl;
        return "";              // pokud soubor neexistuje, navrati prazdy retezec
    }
    std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string vysledek;
    if (!sifrovat)
    {
        posun = -posun;         //desifrovani pretoci posun
    }
    for (char znak : text)
    {
        if (std::isalpha(znak))
        {
            char zaklad = std::islower(znak) ? 'a' : 'A';
            znak = (znak - zaklad + posun + 26) % 26 + zaklad; //presun pismen vramci abecedy
        }
        vysledek += znak;
    }
    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek;
    int delka_klice = klic.length();
    for (size_t i = 0; i < text.length(); i++)
    {
        char znak = text[i];
        if (std::isalpha(znak))
        {
            char zaklad = std::islower(znak) ? 'a' : 'A';
            int posun = (klic[i % delka_klice] - zaklad) * (sifrovat ? 1 : -1);
            znak = (znak - zaklad + posun + 26) % 26 + zaklad;
        }
        vysledek += znak;
    }
    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek;
    int delka_klice = klic.length();
    for (size_t i = 0; i < text.length(); i++)
    {
        vysledek += text[i] ^ klic[i % delka_klice];        // xor operace na vsech znacich
    }
    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open())
    {
        std::cerr << "Nelze otevřít soubor " << jmeno_souboru << " pro zápis." << std::endl;
        return;
    }
    soubor << obsah;
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Caesar: " << sifrovany_text_caesar << std::endl;

    // Šifrování textu pomocí Vigenerovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny", true);
    std::cout << "Vigener: " << sifrovany_text_vigener << std::endl;

    // Šifrování textu pomocí XOR šifry
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "klic", true);
    std::cout << "XOR: " << sifrovany_text_xor << std::endl;

    // Uložení šifrovaných textů do souborů
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

    // Dešifrování textů
    std::cout << "Dešifrovany text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
    std::cout << "Dešifrovany text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny", false) << std::endl;
    std::cout << "Dešifrovany text pomocí XOR šifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "klic", true) << std::endl;

    return 0;
}
#endif // __TEST__
