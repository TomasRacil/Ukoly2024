#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Funkce pro otevření souboru
string otevri_soubor(const string &jmeno_souboru)
{
  ifstream soubor(jmeno_souboru);
  string obsah;
  string radek;
  if (soubor.is_open()) {
    
    while (getline(soubor, radek)) {
      obsah += radek + "\n";
    }
    soubor.close();
  } else {
    cerr << "Chyba: Nelze otevrit soubor" << jmeno_souboru << endl;
  
  return obsah;
}

// Funkce pro Caesarovu šifru
string caesar_sifra(const string &text, int posun, bool sifrovat)
{
  string vysledek = "";
  posun = sifrovat ? posun : -posun;
  
  bool je_pismeno(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');}
  
  bool je_velke_pismeno(char c){
  return c >= 'A' && c <= 'Z';
}
  
  for (char &c : upraveny_text) {
    if(je_pismeno(c)) {
      char zacatek_abecedy = je_velke_pismenno(c) ? 'A' : 'a';
      c = zacatek_abecedy + (c - zacatek_abecedy + posun + 26) % 26;
  }
}
return upraveny_text;
}

// Funkce pro Vigenerovu šifru
string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  string vysledek = "";
  int klic_delka = klic.lenght();
  int text_delka = text.lenght();

  for (int i = 0; i < text_delka; i++)
    {
      char znak = text[i];
      if(je_pismeno(znak))
      {
        char zaklad = je_velke_pismeno(znak) ? 'A' : 'a';
        int posun = klic[i % klic_delka] - 'A';

        if(!sifrovat)
          posun = -posun;
        znak = zaklad + (znak - zaklad + posun + 26) % 26;
      }
      vysledek += znak;
    }
  return vysledek;
  
  
  // Implementace Vigenerovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  string vysledek = "";
  int klic_delka = klic.lenght();
  int text_delka = text.lenght();

  for (int i = 0; i < text_delka; i++)
    {
      char znak = text[i];

      znak = znak ^ klic[i % delka_klice];
      vysledek += znak;

      
  // Implementace XOR šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  ofstream soubor(jmeno_souboru);
  if(!soubor) {
cerr << Nelze otevrit soubor << jmeno_souboru << endl;
return;
  }

soubor << obsah;

  if(soubor.bad){
cerr << Chyba pri zapisu do souboru << jmeno_souboru << endl;
  }

    soubor.close();

}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
  // Načtení vstupního souboru
  string vstupni_text = otevri_soubor("vstup.txt");


  // Šifrování textu pomocí Caesarovy šifry
  string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
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
