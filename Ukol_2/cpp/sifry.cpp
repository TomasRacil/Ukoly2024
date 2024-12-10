#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Funkce pro otevření souboru a načtení obsahu
std::string otevri_soubor(const std::string &jmeno_souboru) {
    std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        // throw std::runtime_error("Nepodařilo se otevřít soubor: " + jmeno_souboru);
        return "";
    }

    std::string obsah((std::istreambuf_iterator<char>(soubor)),
                       std::istreambuf_iterator<char>());
    soubor.close();
    return obsah;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah) {
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        throw std::runtime_error("Nepodařilo se otevřít soubor pro zápis: " + jmeno_souboru);
    }

    soubor << obsah;
    soubor.close();
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat) {
    std::string vysledek;
    int smer = sifrovat ? 1 : -1;

    for (char znak : text) {
        if (std::isalpha(znak)) {
            char base = std::islower(znak) ? 'a' : 'A';
            vysledek += (znak - base + smer * posun + 26) % 26 + base;
        } else {
            vysledek += znak;
        }
    }

    return vysledek;
}

// Funkce pro Vigenerovu šifru (šifrování i dešifrování)
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
    std::string vysledek;
    size_t delka_klice = klic.size();
    int smer = sifrovat ? 1 : -1;

    for (size_t i = 0; i < text.size(); ++i) {
        if (std::isalpha(text[i])) {
            char base = std::islower(text[i]) ? 'a' : 'A';
            char klicove_znak = klic[i % delka_klice];
            char upraveny_klíč = std::islower(klicove_znak) ? klicove_znak - 'a' : klicove_znak - 'A';
            vysledek += (text[i] - base + smer * upraveny_klíč + 26) % 26 + base;
        } else {
            vysledek += text[i];
        }
    }

    return vysledek;
}

// Funkce pro XOR šifru (šifrování i dešifrování)
std::string xor_sifra(const std::string &vstup, const std::string &klic, bool sifrovat) {
    if (klic.empty()) {
        throw std::invalid_argument("Heslo nesmí být prázdné!");
    }

    std::string vysledek;
    size_t delka_klice = klic.size();

    for (size_t i = 0; i < vstup.size(); ++i){ vysledek += vstup[i] ^ klic[i % delka_klice]; }

    return vysledek;
}

#ifndef __TEST__
int main() {
    try {
        // Načtení vstupního souboru
        std::string vstupni_text = otevri_soubor("vstup.txt");

        // Šifrování pomocí Caesarovy šifry
        std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
        uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);

        // Dešifrování pomocí Caesarovy šifry
        std::string desifrovany_text_caesar = caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false);
        std::cout << "Dešifrovaný text Caesar: " << desifrovany_text_caesar << std::endl;

        // Šifrování pomocí XOR šifry
        std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
        uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

        // Dešifrování pomocí XOR šifry
        std::string desifrovany_text_xor = xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false);
        std::cout << "Dešifrovaný text XOR: " << desifrovany_text_xor << std::endl;

        // Šifrování pomocí Vigenerovy šifry
        std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
        uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);

        // Dešifrování pomocí Vigenerovy šifry
        std::string desifrovany_text_vigener = vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false);
        std::cout << "Dešifrovaný text Vigener: " << desifrovany_text_vigener << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Chyba: " << e.what() << std::endl;
    }

    return 0;
}
#endif
