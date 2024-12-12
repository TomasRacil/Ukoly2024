#include <iostream>
#include <fstream>
#include <string>
#include <cctype> 

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream soubor(jmeno_souboru);
    if (!soubor) 
    {
        std::cerr << "Chyba při otevírání souboru!" << std::endl;
        return "";
    }

    std::string obsah;
    std::string radek;
    while (std::getline(soubor, radek)) 
    {
        obsah += radek;
    }

    return obsah;
}
// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string vysledek = text;

    for (int i = 0; i < vysledek.length(); ++i) 
    {
        char &c = vysledek[i];  

        if (isalpha(c)) 
        { 
            char offset = isupper(c) ? 'A' : 'a';  
            if (sifrovat) 
            {
                // Šifrování
                c = (char)(((c - offset + posun) % 26 + 26) % 26 + offset);
            } else 
            {
                // Dešifrování
                c = (char)(((c - offset - posun + 26) % 26 + 26) % 26 + offset);
            }
        }
    }
    return vysledek;
}
// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = text;
    int klic_index = 0;
    int klic_dlouh = klic.length();

    for (int i = 0; i < vysledek.length(); ++i) 
    {
        char &c = vysledek[i];
        if (isalpha(c)) 
        {
            char offset = isupper(c) ? 'A' : 'a';  
            char klic_znak = klic[klic_index % klic_dlouh];  

            if (sifrovat) 
            {
                c = (char)((((c - offset) + (klic_znak - offset)) % 26 + 26) % 26 + offset);  
            } else {
                c = (char)((((c - offset) - (klic_znak - offset) + 26) % 26 + 26) % 26 + offset);  
            }

            klic_index++;  
        }
    }
    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek = text;
    int klic_index = 0;
    int klic_dlouh = klic.length();

    for (int i = 0; i < vysledek.length(); ++i) 
    {
        char &c = vysledek[i];
        c ^= klic[klic_index % klic_dlouh];  
        klic_index++;  
    }
    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    std::ofstream soubor(jmeno_souboru);
    if (!soubor) 
    {
        std::cerr << "Chyba při otevírání souboru pro zápis!" << std::endl;
        return;
    }

    soubor << obsah;
}

#ifndef __TEST__ // Podmíněný překlad pro testování
int main()
{
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Šifrování Caesarovou šifrou: " << sifrovany_text_caesar << std::endl;

    // Šifrování textu pomocí Vigenerovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << "Šifrování Vigenerovou šifrou: " << sifrovany_text_vigener << std::endl;

    // Šifrování textu pomocí XOR šifry
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
    std::cout << "Šifrování XOR šifrou: " << sifrovany_text_xor << std::endl;

    // Uložení šifrovaných textů do souborů
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

    // Dešifrování textů
    std::cout << "Dešifrování textu pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
    std::cout << "Dešifrování textu pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
    std::cout << "Dešifrování textu pomocí XOR šifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

    return 0;
}
#endif // __TEST__