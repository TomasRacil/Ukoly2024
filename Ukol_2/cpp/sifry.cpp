#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru) {
  std::ifstream soubor(jmeno_souboru);
  if (!soubor.is_open()) {
      std::cout << "Nejde otevřít soubor: " <<jmeno_souboru;
      return "";
  }

  std::string data((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>()); //precte cely soubor a nacte vse do 'data' 


  return data;
}

// Funkce pro ulozeni do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &data) {
  std::ofstream soubor(jmeno_souboru);
  if (!soubor.is_open()) {
      std::cout <<"Nejde otevřít soubor: " << jmeno_souboru;
      return;
  }

  soubor << data;
}


// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat) {
  std::string slovo = text;
  char pismeno[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  char Vpismeno[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  for (int i = 0; i < slovo.length(); i++) {
      for (int j = 0; j < 26; j++) {
          if(slovo[i] == pismeno[j]) {
            if(sifrovat)
                slovo[i] = (pismeno[(j + posun) % 26]);
            else
                slovo[i] =(pismeno[(j - posun + 26) % 26]);
            break;
          }
          else if (slovo[i] == Vpismeno[j]){
            if(sifrovat)
              slovo[i]=Vpismeno[(j+posun) % 26];
            else
              slovo[i]=Vpismeno[(j-posun + 26)%26];
            break;
          }
      }
  }
  return slovo;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
  std::string slovo = text;
  int j = 0;
  int delkaklice = klic.length();
  for (int i = 0; i < slovo.length(); i++) {
      char slova = slovo[i];
      if (isalpha(slovo[i])) {
          int x = klic[j % delkaklice] - 'a';
          if (islower(slova)){
            if(sifrovat)
                slovo[i]=(slova -'a'+ x) % 26+'a';
            else
                slovo[i]=(slova-'a'-x +26)%26+'a';
        }else{
            if (sifrovat)
                slovo[i]=(slova-'A'+x) % 26 + 'A';
            else
                slovo[i]=(slova-'A'-x+26) % 26 + 'A';
        }
          j++;
      }
      
  }
  return slovo; 

}



// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
    std::string vysledek;
    if (sifrovat) {
        for (size_t i = 0; i < text.length(); ++i) {
            unsigned char ctext = text[i];
            unsigned char cklic = klic[i % klic.length()];

            unsigned char zasifrovanyChar = ctext ^ cklic;
            vysledek += std::bitset<8>(zasifrovanyChar).to_string() + "  ";
        }
    } else {
        std::string binarniznak;
        std::string desifrovanytext;
        for (size_t i = 0; i < text.length(); i =i+10) {  // +10 protoze bity zabiraji 8 znaku +2 mezera
            binarniznak = text.substr(i, 10);

            std::bitset<8> bits(binarniznak);
            desifrovanytext = desifrovanytext+char(bits.to_ulong()); //zpatky se prevede na ascii hodnotu
        }
        for (size_t i = 0; i < desifrovanytext.length(); ++i) {
            unsigned char ctext = desifrovanytext[i];
            unsigned char cklic = klic[i % klic.length()];

            unsigned char czasifrovany = ctext ^ cklic;
            vysledek += czasifrovany;
        }
    }
    return vysledek;    
}
#ifndef __TEST__  // Add this preprocessor guard
int main() {
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
#endif  // __TEST__