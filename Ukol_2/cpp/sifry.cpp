#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <string.h>
#include <ctype.h>

//arrays for storing alphabet characters
char lowercase_alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char uppercase_alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
  //try to open the file
  ifstream file (jmeno_souboru, ifstream::in);
  if (!file.is_open()) {
    //file is not open
    cerr << "Error opening file " << jmeno_souboru << endl;
    return "";
    if (file.bad()) {
      cerr << "Fatal error: badbit is set!\n";
      return "";
    }
    if (file.fail()) {
      //detiled report according to the error number
      cerr << "Error details: " << strerror(errno) << endl;
      return "";
    }

  }
  string input_txt;
  int c;

  //reading chars so multiple lines can be stored in input_txt
  while(true) {
    c = file.get();
    if (file.eof())
      break;
    input_txt += c;
  }
  file.close();
  return input_txt;
}


char shift_char (char c, int shift) {
  //shifts alphabet char by shift modulo alphabet and returns new char
  return (isupper(c)) ? ((uppercase_alphabet[(26 + c - 'A' + shift) % 26])) : (lowercase_alphabet[(26 + c - 'a' + shift) % 26]);
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
  // Implementace Caesarovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  
  string output;
  for (int i=0;i<text.length();++i)
    //ternary expression: (condition) ? (true) : (false)
    //shift alphabetic characters, skip others
    if(isalpha(text[i]))
      output += (sifrovat) ? (shift_char(text[i], posun)) : (shift_char(text[i], -1 * posun));
    else
      output += text[i];
  
  return output;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace Vigenerovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  string output;
  int posun;
  for (int i=0;i<text.length();++i) {
    //same as Caesar's cipher, but shift of every character is determined by value of corresponding character in keyword
    //if key is too short, it repeats
    //shift alphabetic characters according to calculated shift, skip non_alphabetic characters
    if(isalpha(text[i])) {
      //calculate shift
      posun = (isupper(klic[i % klic.length()])) ? (klic[i % klic.length()] - 'A') : (klic[i % klic.length()] - 'a');
      //if sifrovat is false, shift is passed as negative
      output += (sifrovat) ? (shift_char(text[i], posun)) : (shift_char(text[i], -1 * posun));
    }
    else {
      output += text[i];
    }
  }
    
  return output;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace XOR šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  string output;

  //encoding and decoding is the same function, bool sifrovat is meaningless
  for (int i=0;i<text.length();++i)
    //xor each character with corresponding character in key
    output += (text[i] ^ klic[i % klic.length()]);
  return output;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  // Implementace funkce pro uložení řetězce do souboru
  //try to open the file 

  ofstream out(jmeno_souboru);

  if (!out.is_open()) {
    //file is not open
    cerr << "Error opening file " << jmeno_souboru << endl;
    if (out.bad()) {
      cerr << "Fatal error: badbit is set!\n";
    }
    if (out.fail()) {
      //detailed report according to the error number
      cerr << "Error details: " << strerror(errno) << endl;
    }

  }
  out << obsah;
  out.close();
  return;

}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
  // Načtení vstupního souboru
  std::string vstupni_text = otevri_soubor("vstup.txt");
  if (vstupni_text == "")
    return 1;

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
