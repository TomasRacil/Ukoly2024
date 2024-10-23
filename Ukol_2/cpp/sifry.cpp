#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
  std::ifstream ifs (jmeno_souboru);
  
  if (ifs.is_open()) // Pokud se soubor podaří otevřít, pokračujeme dál
    {
    char t = ifs.get(); // Načteme text ze souboru do proměnné t
    } 
  else 
  {  
    std::cout << "Chyba v načítání souboru" << std::endl; // Pokud se soubor nepodaří otevřít, vypíšeme chybu
  }
  return "";
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
  std::string vysledek = ""; // string do kterého postupně ukládáme zašifrovaný text
  int shift = sifrovat ? 3 : -3; // Posuneme znaky o 3 pozice dopředu při šifrování, jinak zpět

  for (char c : text) // Projde všechny znaky v textu
  {
    if (isalpha(c)) // T9mto zjistíme zda je znak písmeno
    {
      char zakl = isupper(c) ? 'A' : 'a'; // Zjistíme zda je písmeno velké a nebo ne
      c = zakl + (c - zakl + shift + 26) % 26;  // Zjistime zda po přičtení jsme překročili hranici abecedy
      if (c == 'Z' - 1) // Pokud jsme překročili hranici abecedy, posuneme se na začátek
      {
        c = 'a';
      }
    }
    vysledek += c;
  }
  return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  std::string vysledek = "";
  int klic_index = 0; // Index pro postupné procházení klíče
  int klic_delka = klic.length(); // Délka klíče

  for (char c : text) 
  {
    if (isalpha(c)) 
    {
      char zakl = isupper(c) ? 'A' : 'a';
      int shift = (sifrovat ? 1 : -1) * (toupper(klic[klic_index % klic_delka]) - 'A'); // Posuneme znaky podle klíče 
      c = zakl + (c - zakl + shift + 26) % 26; //
      klic_index++;
    }
    vysledek += c;
  }
return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  std::string vysledek = text; // Vytvoříme kopii vstupního textu 
  
  for (size_t i = 0; i < text.size(); ++i) // Projdeme všechny znaky v textu
  {
    vysledek[i] = text[i] ^ klic[i % klic.size()]; // Provedeme operaci XOR mezi znakem textu a klíčem
  }
  return "";
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  std::ofstream out(jmeno_souboru); // Otevřeme soubor pro zápis
  if (out.is_open()) // Pokud se soubor podaří otevřít, pokračujeme dál
  {
    out << obsah; // Zapíšeme obsah do souboru
    out.close(); // Uzavřeme soubor
  } else {
    std::cout << "Chyba při otevírání souboru pro zápis" << std::endl; // Pokud se soubor nepodaří otevřít, vypíšeme chybu
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
