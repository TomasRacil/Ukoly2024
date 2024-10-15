#include <cctype>
#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream soubor(jmeno_souboru, std::ios::in | std::ios::binary);
    if (soubor)
    {
        std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
        soubor.close();
        return obsah;
    }
    else
    {
        std::cerr << "Soubor " << jmeno_souboru << " se nepodarilo otevrit." << std::endl;
        return "";
    }
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string result = text;
    for (std::size_t i = 0; i != text.size(); ++i)
    {
        if (!std::isalpha(text[i])) continue;

        char zaklad = std::isupper(text[i]) ? 'A' : 'a';
        result[i] = (text[i] - zaklad + (sifrovat ? posun : -posun) + 26) % 26 + zaklad;
    }
    return result;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    // Implementace Vigenerovy šifry
    // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
    std::string result = text;
    for (std::size_t i = 0; i != text.size(); ++i)
    {
        result[i] += (sifrovat ? 1 : -1) * (klic[i % klic.size()] - 'a');
    }
    return result;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    if (klic.empty()) return "";
    // sifrovani a desifrovani je stejny
    std::string result = text;
    for (size_t i = 0; i < text.size(); ++i)
        result[i] ^= klic[i % klic.size()];
    return result;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  // Implementace funkce pro uložení řetězce do souboru
  std::ofstream soubor(jmeno_souboru, std::ios::out | std::ios::binary);
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
