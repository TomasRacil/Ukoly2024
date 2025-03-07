#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  // kvůli isalpha, isupper, tolower atd.
#include <algorithm> // kvůli std::transform

/**
 * Funkce pro otevření souboru a načtení jeho obsahu do jednoho řetězce.
 * @param jmeno_souboru Cesta k souboru
 * @return Načtený obsah souboru jako std::string (nebo prázdný řetězec při chybě)
 */
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream ifs(jmeno_souboru, std::ios::in | std::ios::binary);
    if (!ifs.is_open())
    {
        std::cerr << "Chyba: nepodařilo se otevřít soubor '" << jmeno_souboru << "'." << std::endl;
        return {};
    }
    // Načteme obsah souboru do řetězce
    std::string obsah((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));
    return obsah;
}

/**
 * Caesarova šifra pro šifrování/dešifrování.
 *
 * @param text Vstupní text (otevřený nebo zašifrovaný)
 * @param posun Posun (např. 3) – pro dešifrování se použije záporný posun
 *              v případě sifrovat=false.
 * @param sifrovat true -> šifrování, false -> dešifrování
 * @return Výsledný (zašifrovaný či dešifrovaný) text
 *
 * Pozn.: Upravuje pouze písmena [A-Za-z]. Zachovává velikost písmen.
 */
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    // Pokud dešifrujeme, otočíme znaménko posunu
    if (!sifrovat)
    {
        posun = -posun;
    }

    std::string vystup;
    vystup.reserve(text.size());

    for (char c : text)
    {
        if (std::isalpha(static_cast<unsigned char>(c)))
        {
            // Rozlišujeme velká a malá písmena
            if (std::isupper(static_cast<unsigned char>(c)))
            {
                // 'A' má kód 65
                c = static_cast<char>('A' + ( (c - 'A') + posun + 26 ) % 26);
            }
            else
            {
                // 'a' má kód 97
                c = static_cast<char>('a' + ( (c - 'a') + posun + 26 ) % 26);
            }
        }
        vystup.push_back(c);
    }
    return vystup;
}

/**
 * Pomocná funkce k Vigenere – vrací posun podle jednoho znaku klíče.
 * Vycházíme z písmena v klíči (a=0, b=1, ..., z=25).
 */
static int vigenere_posun(char klic_char)
{
    // Budeme pracovat v malých písmenech
    klic_char = static_cast<char>(std::tolower(static_cast<unsigned char>(klic_char)));
    return (klic_char - 'a') % 26; // posun 0..25
}

/**
 * Vigenere šifra pro šifrování/dešifrování.
 * @param text Vstupní text (otevřený nebo zašifrovaný)
 * @param klic Klíčové slovo (např. "tajne")
 * @param sifrovat true -> šifrování, false -> dešifrování
 * @return Výsledný zašifrovaný nebo dešifrovaný text
 *
 * Pozn.: Upravuje pouze písmena [A-Za-z]. Zachovává velikost písmen.
 */
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    if (klic.empty())
    {
        // Bez klíče nic neděláme, vrátíme text beze změn
        return text;
    }

    std::string vystup;
    vystup.reserve(text.size());

    int klic_delka = static_cast<int>(klic.size());
    int j = 0; // index pro procházení klíče

    for (char c : text)
    {
        if (std::isalpha(static_cast<unsigned char>(c)))
        {
            // Zjistíme posun z písmena klíče
            int posun = vigenere_posun(klic[j % klic_delka]);

            if (!sifrovat)
            {
                // Dešifrování => posun záporný
                posun = -posun;
            }

            // Rozlišujeme velká/malá písmena
            if (std::isupper(static_cast<unsigned char>(c)))
            {
                c = static_cast<char>('A' + ((c - 'A') + posun + 26) % 26);
            }
            else
            {
                c = static_cast<char>('a' + ((c - 'a') + posun + 26) % 26);
            }

            j++;
        }
        vystup.push_back(c);
    }
    return vystup;
}

/**
 * XOR šifra: provádí XOR s heslem pro každý znak.
 * Protože XOR je inverzní sama sobě, funkce je stejná pro šifrování i dešifrování.
 *
 * @param text Vstupní text
 * @param klic Klíč (heslo) – zpracovává se po znacích (cyklicky)
 * @param sifrovat true -> "šifruj", false -> "dešifruj" (ve skutečnosti je to totéž)
 * @return Text po XOR operaci
 */
std::string xor_sifra(const std::string &text, const std::string &klic, bool /*sifrovat*/)
{
    if (klic.empty())
    {
        // Bez klíče nic neděláme
        return text;
    }

    std::string vystup = text; // upravujeme kopii
    for (size_t i = 0; i < vystup.size(); i++)
    {
        // Klíč se opakuje cyklicky
        char k = klic[i % klic.size()];
        // Provedeme XOR: result = original ^ key
        vystup[i] = static_cast<char>(vystup[i] ^ k);
    }

    return vystup;
}

/**
 * Uloží daný řetězec do zadaného souboru. Pokud se nepodaří otevřít, vypíše chybu.
 * @param jmeno_souboru Název/cesta k souboru
 * @param obsah Řetězec k uložení
 */
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    std::ofstream ofs(jmeno_souboru, std::ios::out | std::ios::binary);
    if (!ofs.is_open())
    {
        std::cerr << "Chyba: nepodařilo se otevřít soubor '" << jmeno_souboru << "' pro zápis." << std::endl;
        return;
    }
    ofs.write(obsah.data(), static_cast<std::streamsize>(obsah.size()));
}

#ifndef __TEST__
int main()
{
    // 1) Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");
    std::cout << "Nacteno " << vstupni_text.size() << " znaku z 'vstup.txt'." << std::endl;

    // 2) Šifrování textu pomocí Caesarovy šifry
    // posun = 3, sifrovat=true
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Ukazka Caesar sifry: " << sifrovany_text_caesar.substr(0, 50) << " ..." << std::endl;

    // 3) Šifrování textu pomocí Vigenerovy šifry
    // klic = "tajny_klic", sifrovat=true
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << "Ukazka Vigener sifry: " << sifrovany_text_vigener.substr(0, 50) << " ..." << std::endl;

    // 4) Šifrování textu pomocí XOR šifry
    // klic = "heslo", sifrovat=true
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
    std::cout << "Ukazka XOR sifry: " << sifrovany_text_xor.substr(0, 50) << " ..." << std::endl;

    // 5) Uložení šifrovaných textů do souborů
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

    // 6) Dešifrování textů (pokud jsme uložili do souboru, musíme je znovu načíst z disku)
    std::string nacteny_caesar = otevri_soubor("sifrovany_caesar.txt");
    std::string desifrovany_caesar = caesar_sifra(nacteny_caesar, 3, false);
    std::cout << "Dešifrovaný text (Caesar): " << desifrovany_caesar.substr(0, 50) << " ..." << std::endl;

    std::string nacteny_vigener = otevri_soubor("sifrovany_vigener.txt");
    std::string desifrovany_vigener = vigener_sifra(nacteny_vigener, "tajny_klic", false);
    std::cout << "Dešifrovaný text (Vigener): " << desifrovany_vigener.substr(0, 50) << " ..." << std::endl;

    std::string nacteny_xor = otevri_soubor("sifrovany_xor.txt");
    std::string desifrovany_xor = xor_sifra(nacteny_xor, "heslo", false);
    std::cout << "Dešifrovaný text (XOR): " << desifrovany_xor.substr(0, 50) << " ..." << std::endl;

    return 0;
}
#endif // __TEST__
