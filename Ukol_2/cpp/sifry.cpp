#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string& vstup)
{
    // Otevření souboru pro čtení
    std::ifstream soubor(vstup, std::ios::binary);
    if (!soubor.is_open())
    {
        // Chyba při otevírání souboru
        std::cerr << "Chyba při otevírání souboru: " << vstup << std::endl;
        
        return "";
    }

    // Načtení obsahu souboru do řetězce
    std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    soubor.close();
    return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string& text, int posun, bool sifrovat)
{
    // Implementace Caesarovy šifry
    // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
    std::string vysledek = text;
    if (!sifrovat) {
        // Opačný posun pro dešifrování
        posun = -posun; 
    }

    for (char& znak : vysledek) {
        if (isalpha(znak)) {
            // Základní znak (a/A) pro určení posunu
            char base = islower(znak) ? 'a' : 'A';
            // Posun znaku a zajištění cyklického posunu
            znak = (znak - base + posun + 26) % 26 + base;
        }
    }

    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
    // Implementace Vigenerovy šifry
    // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
    std::string vysledek = text;
    size_t delka_klice = klic.length();
    size_t index_klice = 0;

    for (char& znak : vysledek) {
        if (isalpha(znak)) {
            // Základní znak (a/A) pro určení posunu
            char base = islower(znak) ? 'a' : 'A';
            // Určení posunu na základě klíče
            int posun = (islower(klic[index_klice]) ? klic[index_klice] - 'a' : klic[index_klice] - 'A');
            if (!sifrovat) {
                // Opačný posun pro dešifrování
                posun = -posun; 
            }
            // Posun znaku a zajištění cyklického posunu
            znak = (znak - base + posun + 26) % 26 + base;
            // Posun indexu klíče
            index_klice = (index_klice + 1) % delka_klice;
        }
    }

    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
    // XOR šifra funguje stejně pro šifrování i dešifrování
    std::string vysledek = text;
    size_t delka_klice = klic.length();

    if (delka_klice == 0) {
        std::cerr << "Klíč nesmí být prázdný." << std::endl;
        return "";
    }

    for (size_t i = 0; i < vysledek.length(); ++i) {
        // XOR operace mezi znakem textu a znakem klíče
        vysledek[i] = text[i] ^ klic[i % delka_klice];
    }

    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string& nazev_souboru, const std::string& obsah)
{
    // Otevření souboru pro zápis
    std::ofstream soubor(nazev_souboru, std::ios::binary);
    if (!soubor.is_open())
    {
        // Chyba při otevírání souboru
        std::cerr << "Chyba při otevírání souboru: " << nazev_souboru << std::endl;
        return;
    }

    // Zápis obsahu do souboru
    soubor << obsah;
    soubor.close();
}

#ifndef __TEST__ // Přidání preprocesorové podmínky
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
#endif // __TEST__
