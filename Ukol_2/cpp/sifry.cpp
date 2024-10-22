#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype> 
#include <sstream>
#include <iomanip>

using namespace std;

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{

  ifstream file(jmeno_souboru);
  if (!file.is_open()) {
    cerr << "Error: Could not open the file. Check the path." << endl;
    file.close();
    return "";
        
  }else{
    string line;
    getline(file,line);
    file.close();
    return line;
  }



  /*
  fstream file;
  file.open(jmeno_souboru,ios::in);
  if(file.is_open()){
    string line;
    getline(file,line);
    file.close();
    return line;
  }
  file.close();
  return "";
  */
}


string charToOctalEscape(char ch) {
    stringstream ss;
    ss << "\\" << oct << setw(3) << setfill('0') << static_cast<int>(ch);
    return ss.str();
}

string octalEscapeToChar(const string& octalStr) {
    string result;
    size_t i = 0;

    while (i < octalStr.length()) {
        if (octalStr[i] == '\\') {

            string octalValue = octalStr.substr(i + 1, 3);
            int asciiValue = stoi(octalValue, nullptr, 8);


            result += static_cast<char>(asciiValue);

            i += 4;
        } else {

            result += octalStr[i];
            i++;
        }
    }

    return result;
}



// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{

  // Implementace Caesarovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  string lowerCaseText = text;
  transform(lowerCaseText.begin(),lowerCaseText.end(), lowerCaseText.begin(), ::tolower);
  

  if(posun<0){
    posun = 26 + (posun%26); 
  }else if(posun>26){
    posun = posun % 26;
  }


  if(sifrovat){
    char* charArray = new char[text.length()+1];
    for(int i = 0; i < text.length(); i++){
      if(lowerCaseText[i]+posun<=122){
        charArray[i] = lowerCaseText[i] + posun;
      }else{
        charArray[i] = lowerCaseText[i] + posun - 26;
      }
    }
    string str(charArray);
    return charArray;
  }else{
    char* charArray = new char[lowerCaseText.length()+1];
    for(int i = 0; i < lowerCaseText.length(); i++){
      charArray[i] = lowerCaseText[i] - posun;
    }
    string str(charArray);
    return charArray;
  }  
}



// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{

  string lowerCaseText = text;
  transform(lowerCaseText.begin(),lowerCaseText.end(), lowerCaseText.begin(), ::tolower);
  string lowerCaseKey = klic;
  transform(lowerCaseKey.begin(),lowerCaseKey.end(), lowerCaseKey.begin(), ::tolower);

  char* charArray = new char[lowerCaseText.length()+1];
  int j = 0;
  int keyLength = klic.length();

  if(sifrovat){
      for(int i = 0; i < lowerCaseText.length();i++){
        if(lowerCaseText[i] + lowerCaseKey[i] - 97 < 122){
          charArray[i] = lowerCaseText[i] + lowerCaseKey[j] - 97;
        }else{
          charArray[i] = lowerCaseText[i] + lowerCaseKey[j] - 123;
        }
        j++;
        if(j>keyLength){
          j = 0;
        }
      }  
      string str(charArray);
      return charArray;
  }else{
      for(int i = 0; i < lowerCaseText.length();i++){
        if(lowerCaseText[i] - lowerCaseKey[i] + 97 > 96){
          charArray[i] = lowerCaseText[i] - lowerCaseKey[j] + 97;
        }else{
          charArray[i] = lowerCaseText[i] - lowerCaseKey[j] + 123;
        }
        j++;
        if(j>keyLength){
          j = 0;
        }
      }
      string str(charArray);
      return charArray;
  }
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    string result;
    int keyLength = klic.length();
    if(sifrovat){

      for (int i = 0; i < text.length(); i++) {      
          char xorResult = text[i] xor klic[i % keyLength];
          result += charToOctalEscape(xorResult);
      }

      return result;
    }else{
      string notOctalEscape = octalEscapeToChar(text);
      for(int i = 0; i < notOctalEscape.length();i++){
          char xorResult = notOctalEscape[i] xor klic[i % keyLength];
          result += xorResult;
      }  
  
     
    }
}



// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  // Implementace funkce pro uložení řetězce do souboru

  ofstream file(jmeno_souboru);
  if(!file.is_open()){

    cerr << "Error: Could not open the file for writing!" << endl;
    file.close();  

  }else{
    file << obsah << endl;
    file.close();
    cout << "Data written to file "<< jmeno_souboru <<" successfully." << endl;
  
  }
  file.close();
  
  /*
  fstream file;
  file.open(jmeno_souboru, ios::out);
  if(file.is_open()){
    file << obsah; 
  }
  file.close();

  */

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
