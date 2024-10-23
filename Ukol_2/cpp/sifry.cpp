#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru a načtení jeho obsahu
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream soubor(jmeno_souboru);
    if (!soubor)
    {
        std::cerr << "Chyba při otevírání souboru: " << jmeno_souboru << std::endl;
        return "";
    }
    std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string vysledek = "";
    int real_posun = sifrovat ? posun : 26 - posun; // Opačný posun pro dešifrování

    for (char ch : text)
    {
        if (isupper(ch))
            vysledek += char(int(ch + real_posun - 65) % 26 + 65);
        else if (islower(ch))
            vysledek += char(int(ch + real_posun - 97) % 26 + 97);
        else
            vysledek += ch; // Nepísmena nešifrujeme
    }
    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = "";
    int delka_klice = klic.length();

    for (size_t i = 0; i < text.length(); ++i)
    {
        char ch = text[i];
        int posun = klic[i % delka_klice] - 'a'; // Posun podle klíčového slova
        if (!sifrovat)
            posun = 26 - posun; // Opačný posun pro dešifrování

        if (isupper(ch))
            vysledek += char((ch - 'A' + posun) % 26 + 'A');
        else if (islower(ch))
            vysledek += char((ch - 'a' + posun) % 26 + 'a');
        else
            vysledek += ch; // Nepísmena nešifrujeme
    }
    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = "";
    int delka_klice = klic.length();

    for (size_t i = 0; i < text.length(); ++i)
    {
        vysledek += text[i] ^ klic[i % delka_klice]; // XOR operace
    }
    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    std::ofstream soubor(jmeno_souboru);
    if (!soubor)
    {
        std::cerr << "Chyba při otevírání souboru pro zápis: " << jmeno_souboru << std::endl;
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

    if (vstupni_text.empty()) {
        std::cerr << "Soubor 'vstup.txt' neexistuje nebo je prázdný." << std::endl;
        return 1;
    }

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Caesarova šifra (šifrovaný text): " << sifrovany_text_caesar << std::endl;

    // Šifrování textu pomocí Vigenerovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajnyklic", true);
    std::cout << "Vigenerova šifra (šifrovaný text): " << sifrovany_text_vigener << std::endl;

    // Šifrování textu pomocí XOR šifry
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
    std::cout << "XOR šifra (šifrovaný text): " << sifrovany_text_xor << std::endl;

    // Uložení šifrovaných textů do souborů
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

    // Dešifrování textů
    std::cout << "Dešifrovany text pomocí Caesarovy šifry: " 
              << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
    std::cout << "Dešifrovany text pomocí Vigenerovy šifry: " 
              << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajnyklic", false) << std::endl;
    std::cout << "Dešifrovany text pomocí XOR šifry: " 
              << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

    return 0;
}
#endif // __TEST__

