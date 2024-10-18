#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
  string vstupni_text = "";
  // Implementace funkce pro otevření souboru a načtení jeho obsahu
  fstream myFile;
  myFile.open(jmeno_souboru, ios::in);
  if(myFile.is_open()) 
  {
    string radek;
    while(getline(myFile,radek)) 
    {
      vstupni_text += radek + "\n";
    }
    myFile.close();
    return vstupni_text;
  }    
  else
  {
    return "Soubor se nepodařilo otevřít";
  }

}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
  // Implementace Caesarovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrován
  if(sifrovat == true)
  {
    string sifrovany_text_caesar = "";
    for(int i = 0; i < text.length(); i++)
    {
      if(isalpha(text[i]))
      {
        if(isupper(text[i]))
        {
          sifrovany_text_caesar += char(int(text[i] + posun - 65) % 26 + 65);
        }
        else
        {
          sifrovany_text_caesar += char(int(text[i] + posun - 97) % 26 + 97);
        }
      }
      else
      {
        sifrovany_text_caesar += text[i];
      }
    }
    return sifrovany_text_caesar;
  }
  else
  {
    string sifrovany_text_ceasar = "";
    for(int i = 0; i < text.length(); i++)
    {
      if(isalpha(text[i]))
      {
        if(isupper(text[i]))
        {
          sifrovany_text_ceasar += char(int(text[i] - posun - 65 + 26) % 26 + 65);
        }
        else
        {
          sifrovany_text_ceasar += char(int(text[i] - posun - 97 + 26) % 26 + 97);
        }
      }
      else
      {
        sifrovany_text_ceasar += text[i];
      }
    }
    return sifrovany_text_ceasar;
  }
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace Vigenerovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  if(sifrovat == true)
  {
    string sifrovany_text_vigener = "";
    for(int i = 0; i < text.length(); i++)
    {
      if(isalpha(text[i]))
      {
        if(isupper(text[i]))
        {
          sifrovany_text_vigener += char(int(text[i] + klic[i % klic.length()] - 2 * 65) % 26 + 65);
        }
        else
        {
          sifrovany_text_vigener += char(int(text[i] + klic[i % klic.length()] -2  * 97) % 26 + 97);
        }
      }
      else
      {
        sifrovany_text_vigener += text[i];
      }
    }
    return sifrovany_text_vigener;
  }
  else
  {
    string sifrovany_text_vigener = "";
    for(int i = 0; i < text.length(); i++)
    {
      if(isalpha(text[i]))
      {
        if(isupper(text[i]))
        {
          sifrovany_text_vigener += char(int(text[i] - klic[i % klic.length()] + 26) % 26 + 65);
        }
        else
        {
          sifrovany_text_vigener += char(int(text[i] - klic[i % klic.length()] + 26) % 26 + 97);
        }
      }
      else
      {
        sifrovany_text_vigener += text[i];
      }
    }
    return sifrovany_text_vigener;

  }

  return "";
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace XOR šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  if(sifrovat == true)
  {
    string sifrovany_text_xor = "";
    for(int i = 0; i < text.length(); i++)
    {
      sifrovany_text_xor += text[i] ^ klic[i % klic.length()];

    }
    return sifrovany_text_xor;
  }
  else
  {
    string sifrovany_text_xor = "";
    for(int i = 0; i < text.length(); i++)
    {
      sifrovany_text_xor += text[i] ^ klic[i % klic.length()];
    }
    return sifrovany_text_xor;
  }
  return "";
}
  

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  // Implementace funkce pro uložení řetězce do souboru
  fstream myFile;
  myFile.open(jmeno_souboru, ios::out);
  if(myFile.is_open())
  {
    myFile << obsah;
    myFile.close();
  }
  else
  {
    cout << "Soubor se nepodařilo otevřít" << endl;
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