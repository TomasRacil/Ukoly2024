#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <map>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open())
    {
        return ""; // Pokud soubor neexistuje, vrátíme prázdný řetězec
    }
    return std::string((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string vysledek;
    int smer = sifrovat ? 1 : -1; // Posun se přičítá při šifrování a odčítá při dešifrování
    for (char znak : text)
    {
        if (std::isalpha(znak))
        {
            char zaklad = std::islower(znak) ? 'a' : 'A';
            znak = (znak - zaklad + smer * posun + 26) % 26 + zaklad;
        }
        vysledek += znak;
    }
    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek;
    int smer = sifrovat ? 1 : -1;
    int delka_klice = klic.size();
    for (size_t i = 0; i < text.size(); ++i)
    {
        char znak = text[i];
        if (std::isalpha(znak))
        {
            char zaklad = std::islower(znak) ? 'a' : 'A';
            char klic_znak = std::tolower(klic[i % delka_klice]) - 'a';
            znak = (znak - zaklad + smer * klic_znak + 26) % 26 + zaklad;
        }
        vysledek += znak;
    }
    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string vysledek;
    size_t delka_klice = klic.size();
    for (size_t i = 0; i < text.size(); ++i)
    {
        vysledek += text[i] ^ klic[i % delka_klice];
    }
    return vysledek;
}

// Funkce pro Playfairovu šifru (bonus)
std::string playfair_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    // Předzpracování klíče: vytvoření matice
    std::map<char, std::pair<int, int>> mapa;
    char matice[5][5];
    std::string abeceda = "abcdefghiklmnopqrstuvwxyz";
    std::string upraveny_klic;
    std::vector<bool> pouzity_znak(26, false);
    for (char c : klic)
    {
        if (std::isalpha(c))
        {
            c = std::tolower(c);
            if (c == 'j')
                c = 'i';
            if (!pouzity_znak[c - 'a'])
            {
                pouzity_znak[c - 'a'] = true;
                upraveny_klic += c;
            }
        }
    }
    for (char c : abeceda)
    {
        if (!pouzity_znak[c - 'a'])
        {
            upraveny_klic += c;
            pouzity_znak[c - 'a'] = true;
        }
    }
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            char c = upraveny_klic[i * 5 + j];
            matice[i][j] = c;
            mapa[c] = {i, j};
        }
    }

    // Zpracování textu
    std::string upraveny_text;
    for (char c : text)
    {
        if (std::isalpha(c))
        {
            c = std::tolower(c);
            if (c == 'j')
                c = 'i';
            upraveny_text += c;
        }
    }
    if (upraveny_text.size() % 2 != 0)
        upraveny_text += 'x';

    std::string vysledek;
    for (size_t i = 0; i < upraveny_text.size(); i += 2)
    {
        char a = upraveny_text[i];
        char b = upraveny_text[i + 1];
        auto [ax, ay] = mapa[a];
        auto [bx, by] = mapa[b];
        if (ax == bx)
        {
            vysledek += matice[ax][(ay + (sifrovat ? 1 : 4)) % 5];
            vysledek += matice[bx][(by + (sifrovat ? 1 : 4)) % 5];
        }
        else if (ay == by)
        {
            vysledek += matice[(ax + (sifrovat ? 1 : 4)) % 5][ay];
            vysledek += matice[(bx + (sifrovat ? 1 : 4)) % 5][by];
        }
        else
        {
            vysledek += matice[ax][by];
            vysledek += matice[bx][ay];
        }
    }
    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    std::ofstream soubor(jmeno_souboru);
    if (soubor.is_open())
    {
        soubor << obsah;
    }
}
#ifndef __TEST__ // Add this preprocessor guard
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
