#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Funkce pro otevření souboru a načtení jeho obsahu
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        throw std::runtime_error("Soubor se nepodařilo otevřít.");
    }

    std::string obsah;
    std::string radek;
    while (std::getline(soubor, radek)) {
        obsah += radek + "\n";
    }
    soubor.close();
    return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string vysledek = "";
    posun = sifrovat ? posun : -posun;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = base + (c - base + posun + 26) % 26;
        }
        vysledek += c;
    }

    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = "";
    int klic_index = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int shift = toupper(klic[klic_index % klic.size()]) - 'A';
            if (!sifrovat) {
                shift = -shift;
            }
            c = base + (c - base + shift + 26) % 26;
            klic_index++;
        }
        vysledek += c;
    }
    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = "";
    int klic_index = 0;
    for (char c : text) {
        // XOR operace mezi znakem textu a znakem hesla
        char xor_char = c ^ klic[klic_index % klic.size()];
        vysledek += xor_char;
        klic_index++;
    }
    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        throw std::runtime_error("Soubor se nepodařilo otevřít pro zápis.");
    }
    soubor << obsah;
    soubor.close();
}

#ifndef __TEST__ // Preprocesorová ochrana pro testování
int main()
{
    try {
        // Načtení vstupního souboru
        std::string vstupni_text = otevri_soubor("vstup.txt");

        // Šifrování textu pomocí Caesarovy šifry
        std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
        std::cout << "Caesarova šifra (šifrování):\n" << sifrovany_text_caesar << std::endl;

        // Šifrování textu pomocí Vigenerovy šifry
        std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
        std::cout << "Vigenerova šifra (šifrování):\n" << sifrovany_text_vigener << std::endl;

        // Šifrování textu pomocí XOR šifry
        std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
        std::cout << "XOR šifra (šifrování):\n" << sifrovany_text_xor << std::endl;

        // Uložení šifrovaných textů do souborů
        uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
        uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
        uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

        // Dešifrování textů
        std::cout << "Dešifrovany text pomocí Caesarovy šifry:\n"
                  << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;

        std::cout << "Dešifrovany text pomocí Vigenerovy šifry:\n"
                  << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;

        std::cout << "Dešifrovany text pomocí XOR šifry:\n"
                  << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Chyba: " << e.what() << std::endl;
    }

    return 0;
}
#endif // __TEST__
