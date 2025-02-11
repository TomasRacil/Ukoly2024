#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru a načtení jeho obsahu do řetězce
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        std::cerr << "Chyba: Nepodařilo se otevřít soubor: " << jmeno_souboru << std::endl;
        return "";
    }

    std::string obsah;
    std::string radek;
    while (std::getline(soubor, radek)) {
        obsah += radek + "\n"; // Přidáme každý řádek do výsledného řetězce
    }
    soubor.close();
    return obsah;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        std::cerr << "Chyba: Nepodařilo se uložit do souboru: " << jmeno_souboru << std::endl;
        return;
    }

    soubor << obsah;
    soubor.close();
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string vysledek = "";
    int real_posun = sifrovat ? posun : -posun;

    for (char znak : text) {
        if (isalpha(znak)) {
            char zaklad = islower(znak) ? 'a' : 'A'; // Rozlišujeme mezi malými a velkými písmeny
            znak = zaklad + (znak - zaklad + real_posun + 26) % 26;
        }
        vysledek += znak;
    }

    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
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
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = "";
    int klic_delka = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        vysledek += text[i] ^ klic[i % klic_delka]; // XOR operace mezi textem a klíčem
    }

    return vysledek;
}

#ifndef __TEST__
int main()
{
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");
    if (vstupni_text.empty()) {
        std::cerr << "Chyba: Soubor vstup.txt je prázdný nebo neexistuje." << std::endl;
        return 1;
    }

    // Caesarova šifra: posun o 3
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Caesarova šifra: " << sifrovany_text_caesar << std::endl;
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);

    // Vigenerova šifra: klíč "tajny_klic"
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << "Vigenerova šifra: " << sifrovany_text_vigener << std::endl;
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);

    // XOR šifra: heslo "heslo"
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
    std::cout << "XOR šifra: " << sifrovany_text_xor << std::endl;
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

    // Dešifrování textů
    std::cout << "Dešifrovaný text pomocí Caesarovy šifry: " 
              << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;

    std::cout << "Dešifrovaný text pomocí Vigenerovy šifry: " 
              << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;

    std::cout << "Dešifrovaný text pomocí XOR šifry: " 
              << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

    return 0;
}
#endif // __TEST__
