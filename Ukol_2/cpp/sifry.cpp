#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;
// funkce pro otevreni souboru
string otevri_soubor(const string &jmeno_souboru)
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
// nacteni souboru do stringu
  while(f.get(tmp)){
    text += tmp;
  }
  // zavru soubor
  f.close();
  return text;
}
// Caesarova šifra
string caesar_sifra(const string &text, int posun, bool sifrovat)
{
  string upravenytext = text;
  for (int i = 0; i < text.length(); ++i) {
        char &tmp = upravenytext[i];
        if (isalpha(tmp)) {
            char p = isupper(tmp) ? 'A' : 'a';
            if (sifrovat) {
                tmp = (char)(((tmp - p + posun) % 26 + 26) % 26 + p);
            } else {
                tmp = (char)(((tmp - p - posun + 26) % 26 + 26) % 26 + p);
            }
        }
    }
  return upravenytext;
}
// Vigenerova šifra
string vigener_sifra(const string &text, const string &klic, bool sifrovat)
{
  string upravenytext = text;
  char x = 0;
  // sifruju
  if(sifrovat == true){
    for(int i = 0; i < text.length(); i++){
      if(isupper(text[i])){
        x = 65;
      }else{
        x = 97;
      }
      int posun = klic[i % klic.size()] - x;
      upravenytext[i] = (text[i] - x + posun + 26) % 26 + x;
    }
  }
  // desifruju
  if(sifrovat == false){
    for(int i = 0; i < text.length(); i++){
      if(isupper(text[i])){
        x = 65;
      }else{
        x = 97;
      }
      int posun = klic[i % klic.size()] - x;
      upravenytext[i] = (text[i] - x - posun + 26) % 26 + x;
    }
  }
  return upravenytext;
}
// XOR šifra
string xor_sifra(const string &text, const string &klic, bool sifrovat)
{
  string upravenytext = text;

  for(int i = 0; i < text.length(); ++i){
    upravenytext[i] = text[i] ^ klic[i % klic.length()]; // ^ operator pro binarni XOR
  }

  return upravenytext;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const string &jmeno_souboru, const string &obsah)
{
  // otevru soubor pro zapisovani, pokud neexistuje tak ho vytvorim
  ofstream MyFile(jmeno_souboru);

  // zapisu do souboru
  MyFile << obsah;

  // zavru soubor
  MyFile.close();
}

#ifndef __TEST__ // Add this preprocessor guard
int main(){
  // Načtení vstupního souboru
  string vstupni_text = otevri_soubor("vstup.txt");

  // Šifrování textu pomocí Caesarovy šifry
  string sifrovany_text_caesar = caesar_sifra(vstupni_text, 25, true);
  cout << sifrovany_text_caesar << endl;

  // Šifrování textu pomocí Vigenerovy šifry
  string sifrovany_text_vigener = vigener_sifra(vstupni_text, "hlgu", true);
  cout << sifrovany_text_vigener << endl;

  // Šifrování textu pomocí XOR šifry
  string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
  cout << sifrovany_text_xor << endl;

  // Uložení šifrovaných textů do souborů
  uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
  uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
  uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

  // Dešifrování textů
  cout << "Dešifrovany text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 25, false) << endl;
  cout << "Dešifrovany text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "hlgu", false) << endl;
  cout << "Dešifrovany text pomocí XOR šifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << endl;

  return 0;
} 
#endif // __TEST__
