#include <iostream>
#include <fstream>
#include <string>

// Funkce jenž umožňuje otevřít soubor a načíst jeho obsah
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    // Otevření souboru potřebného pro přečtení
    std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open()) // Pokud nelze soubor otevřít
    {
        // Výpis chyby do konzole programu
        std::cerr << "Nepodarilo se otevrit soubor: " << jmeno_souboru << std::endl;
        return ""; // Výpis prázdného řádku
    }

    // Načtení celého obsahu souboru do řetězce
    std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    soubor.close(); // Zavření souboru
    return obsah; // Návrat obsahu zpět do souboru
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string vysledek = ""; // Výslednů řetězce po zpracování obsahu Ceasarovou šifrou
    for (char c : text) // Pro každý znak v textu
    {
        if (isalpha(c)) // Pokud je znak písmeno
        {
            char offset = isupper(c) ? 'A' : 'a'; // Rozlišení mezi velkými a malými písmeny
            int shift = sifrovat ? posun : -posun; // Určení zda šifrujeme nebo dešifrujeme
            vysledek += (c - offset + shift + 26) % 26 + offset; // Vložení zašifrovaného písmene zpět do řetězce
        }
        else
        {
            vysledek += c; // Symboly jenž nejsou písmena nejsou ovlivněna
        }
    }
    return vysledek; // Návrat zašifrovaného textu
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = ""; // Výsledný řetězce po zpracování obsahu Vigenerovu šifru
    int delka_klice = klic.size(); // Zjištění délky klíče

    for (size_t i = 0; i < text.size(); ++i) // Pro každý znak v textu
    {
        char c = text[i]; // Aktuální znak textu
        if (isalpha(c)) // Pokud je znak písmeno
        {
            char offset = isupper(c) ? 'A' : 'a'; // Rozlišení mezi velkými a malými písmeny
            char k = isupper(klic[i % delka_klice]) ? klic[i % delka_klice] - 'A' : klic[i % delka_klice] - 'a'; // Vypočet posunu podle klíče
            int shift = sifrovat ? k : -k; // Určení zda šifrujeme nebo dešifrujeme
            vysledek += (c - offset + shift + 26) % 26 + offset; // Vložení zašifrovaného písmene zpět do řetězce
        }
        else
        {
            vysledek += c; // Symboly jenž nejsou písmena nejsou ovlivněna
        }
    }
    return vysledek; // Návrat zašifrovaného textu
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = ""; // Výsledný řetězce po zpracování obsahu XOR šifrou
    int delka_klice = klic.size(); // Zjištění délky klíče

    for (size_t i = 0; i < text.size(); ++i) // Pro každý znak v textu
    {
        vysledek += text[i] ^ klic[i % delka_klice]; // Šifrování obsahu pomocí XOR (interakce mezi znakem textu a klíčem)
    }

    return vysledek; // Návrat zašifrovaného textu
}

// Funkce umožňujicí uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    // Otevření souboru pro zápis
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open()) // Pokud nelze soubor otevřít
    {
        // Výpis chyby do konzole programu
        std::cerr << "Nepodarilo se otevrit soubor pro zapis: " << jmeno_souboru << std::endl;
        return;
    }

    soubor << obsah; // Zápis obsahu do souboru
    soubor.close(); // Zavření souboru
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");

    if (vstupni_text.empty()) // Pokud vstupní soubour neobsahuje text
    {
        // Výpis chyby do konzole a ukončení programu
        std::cerr << "Chyba: vstupni soubor neobsahuje zadny text." << std::endl;
        return 1;
    }

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true); // Zašifrování textu s posunem o 3 znaky
    std::cout << "Caesarova sifra: " << sifrovany_text_caesar << std::endl; // Výpis upraveného textu

    // Šifrování textu pomocí Vigenerovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true); // Zašifrování textu pomocí klíče "tajny_klic"
    std::cout << "Vigenerova sifra: " << sifrovany_text_vigener << std::endl; // Výpis upraveného textu

    // Šifrování textu pomocí XOR šifry
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true); // Zašifrování textu pomocí XOR a klíče "heslo"
    std::cout << "XOR sifra: " << sifrovany_text_xor << std::endl; // Výpis upraveného textu

    // Uložení zašifrovaných textů do souborů
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar); // Uložení Caesarovu šifru do souboru
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener); // Uložení Vigenerovu šifru do souboru
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor); // Uložení XOR šifru do souboru

    // Dešifrování textů a jejich zobrazení
    std::cout << "Desifrovany text pomoci Caesarovy sifry: " 
              << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl; // Načtení a dešifrovnáí Caesarovu šifru
    std::cout << "Desifrovany text pomoci Vigenerovy sifry: " 
              << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl; // Načtení a dešifrování Vigenerovu šifru
    std::cout << "Desifrovany text pomoci XOR sifry: " 
              << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl; // Načtení a dešifrování XOR šifru

    return 0; // Konec programu
}
#endif // __TEST__
