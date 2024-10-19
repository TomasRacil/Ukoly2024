#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Funkce pro otevření souboru
string otevri_soubor(const string &jmeno_souboru)
{
  ifstream soubor(jmeno_souboru);
  string obsah;
  if (soubor.is_open()) {
    string radek;
    while (getline(soubor, radek)) {
      obsah += radek + "\n";
    }
    soubor.close();
  }
  
  return obsah;
}

// Funkce pro Caesarovu šifru
string caesar_sifra(const string &text, int posun, bool sifrovat)
{
  string upraveny_text = text;
  posun = sifrovat ? posun : -posun;

  
  for (char &c : upraveny_text) {
    if(isalpha(c)):
      char zacatek_abecedy = isupper(c) ? 'A' : 'a';
      c = zacatek_abecedy + (c - zacatek_abecedy + posun + 26) % 26;
  }
}
return upraveny_text;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace Vigenerovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  return "";
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace XOR šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  return "";
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  // Implementace funkce pro uložení řetězce do souboru
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
  // Načtení vstupního souboru
  string vstupni_text = otevri_soubor("vstup.txt");

  if(!vstupni_text.empty()) {
    cout << "Obsah souboru:" << endl;
    cout << vstupni_text << endl;
  }
  else {
    cout << "Soubor je prazdny" << endl;

    return 0;
  }
  
  

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
