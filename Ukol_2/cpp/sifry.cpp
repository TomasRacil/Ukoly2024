#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
  // Implementace funkce pro otevření souboru a načtení jeho obsahu
  std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open())
    {
        std::cerr << "Nepodařilo se otevřít soubor: " << jmeno_souboru << std::endl;
        return "";
    }

    std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    soubor.close();
    return obsah;

  
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
  // Implementace Caesarovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
   std::string vysledek = text;
    posun = sifrovat ? posun : -posun;

    for (char &znak : vysledek)
    {
        if (isalpha(znak))
        {
            char base = islower(znak) ? 'a' : 'A';
            znak = static_cast<char>((znak - base + posun + 26) % 26 + base);
        }
    }
    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace Vigenerovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  std::string vysledek = text;
    int delka_klice = klic.size();

    for (size_t i = 0; i < text.size(); ++i)
    {
        char posun = klic[i % delka_klice] - 'A';
        posun = sifrovat ? posun : -posun;

        if (isalpha(text[i]))
        {
            char base = islower(text[i]) ? 'a' : 'A';
            vysledek[i] = static_cast<char>((text[i] - base + posun + 26) % 26 + base);
        }
    }
    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace XOR šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  std::string vysledek = text;
    int delka_klice = klic.size();

    for (size_t i = 0; i < text.size(); ++i)
    {
        vysledek[i] = text[i] ^ klic[i % delka_klice];
    }
    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  // Implementace funkce pro uložení řetězce do souboru
  std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open())
    {
        std::cerr << "Nepodařilo se uložit do souboru: " << jmeno_souboru << std::endl;
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