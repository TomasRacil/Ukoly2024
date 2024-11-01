#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
  string text;
  char tmp;
  // otevru soubor
  ifstream f(jmeno_souboru, ifstream::in);

// kontrola jestli se soubor otevrel
  if (!f.is_open()){
    cerr << "Soubor " << jmeno_souboru << " se nepodarilo otevrit." << endl; // kdyz se soubor neotevre, kod ukoncim a vypisu chybovou spravu
    return"";
  }
  while(f.get(tmp)){
    text += tmp;
  }
  return text;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
{
  string upravenytext = text;
  // sifruju
  if(sifrovat == true){
    for(int i = 0; i < text.length(); i++){
      // pokud bych posunutim vysel z range pismen v ascii, odectu 26, abych v nem zustal
      if(isalpha(text[i] + posun)){
        upravenytext[i] = text[i] + posun;
      }else{
        upravenytext[i] = text[i] + posun - 26;
      }
    }

  // desifruju
  }else{
    for(int i = 0; i < text.length(); ++i){
      // stejne jako u sifrovani, akorat pricitam 26
      if(isalpha(text[i] - posun)){
        upravenytext[i] = text[i] - posun;
      }else{
        upravenytext[i] = text[i] - posun + 26;
      }
    }
  }
  return upravenytext;
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
  string upravenytext = text;

  for(int i = 0; i < text.length(); ++i){
    upravenytext[i] = text[i] ^ klic[i % klic.length()]; // ^ operator pro binarni XOR
  }

  return upravenytext;
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
