#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
  // Implementace funkce pro otevření souboru a načtení jeho obsahu
  ifstream soubor_vstup(jmeno_souboru);
  if (!soubor_vstup.is_open()) {
    std::cerr << "Failed to open the file!" << std::endl;
    return "";
  }

   std::stringstream buffer;
    buffer << soubor_vstup.rdbuf(); // Read the file content into the stringstream

    std::string fileContent = buffer.str();
  return fileContent;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
  // Implementace Caesarovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  string result = "";

  if (sifrovat==true){
    for (char ch : text) {
        // Pokud je znak velké písmeno
        if (std::isupper(ch)) {
            result += char(int(ch + posun - 'A') % 26 + 'A');
        }
        // Pokud je znak malé písmeno
        else if (std::islower(ch)) {
            result += char(int(ch + posun - 'a') % 26 + 'a');
        }
        // Pokud je znak jiný (nepísmeno), nepřepisuje se
        else {
            result += ch;
        }
    }
  }

  else if (sifrovat==false) {
    std::string result = "";

    // Procházení každého znaku v šifrovaném textu
    for (char ch : text) {
        // Pokud je znak písmeno
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A'; // Určení základního znaku (malá nebo velká písmena)
            // Dešifrování znaku
            char decryptedChar = (ch - base - posun + 26) % 26 + base;
            result += decryptedChar; // Přidání dešifrovaného znaku do výsledného textu
        } else {
            result += ch; // Pokud není písmeno, přidáme ho nezměněný
        }
    }
    return result;
  }
  return result;
}


// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
  // Implementace Vigenerovy šifry
  // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
  string result;
  if (sifrovat==true){
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        char currentChar = text[i];
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            currentChar = (currentChar - base + (toupper(klic[keyIndex]) - 'A')) % 26 + base;
            keyIndex = (keyIndex + 1) % klic.length();
        }
        result += currentChar; // Nešifrované znaky (např. mezery) se přidávají bez změny
    }

  }
  if (sifrovat==false) {
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        char currentChar = text[i];
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            currentChar = (currentChar - base - (toupper(klic[keyIndex]) - 'A') + 26) % 26 + base;
            keyIndex = (keyIndex + 1) % klic.length();
        }
        result += currentChar;
    }
  }
  return result;
}

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

// Funkce pro převod osmičkového řetězce na binární data
std::string octalToBytes(const std::string &octal) {
    std::string bytes;
    for (size_t i = 0; i < octal.length(); i += 3) {
        std::string byteString = octal.substr(i, 3);
        char byte = static_cast<char>(std::stoi(byteString, nullptr, 8));  // Převod z osmičkové soustavy
        bytes.push_back(byte);
    }
    return bytes;
}

// Funkce pro převod binárních dat na osmičkový řetězec
std::string bytesToOctal(const std::string &bytes) {
    std::ostringstream oss;
    for (unsigned char c : bytes) {
        oss << std::setw(3) << std::setfill('0') << std::oct << static_cast<int>(c);  // Převede na osmičkovou soustavu
    }
    return oss.str();
}

// Funkce pro XOR šifrování a dešifrování v osmičkové soustavě
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
    std::string result;
    size_t keyLength = klic.length();

    if (keyLength == 0) {
        throw std::invalid_argument("Klíč nesmí být prázdný.");
    }

    if (sifrovat) {
        // Šifrování: XOR každého znaku a převod na osmičkový řetězec
        for (size_t i = 0; i < text.length(); ++i) {
            char encryptedChar = text[i] ^ klic[i % keyLength];
            result += bytesToOctal(std::string(1, encryptedChar));  // Převede zašifrovaný znak na osmičkový řetězec
        }
    } else {
        // Dešifrování: převede osmičkový řetězec na znaky a aplikuje XOR s klíčem
        std::string bytes = octalToBytes(text);  // Převede osmičkový řetězec na binární data
        for (size_t i = 0; i < bytes.length(); ++i) {
            result += bytes[i] ^ klic[i % keyLength];  // Aplikuje XOR s klíčem
        }
    }

    return result;
}



// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
  // Implementace funkce pro uložení řetězce do souboru
  std::ofstream outFile(jmeno_souboru); // Otevření souboru pro zápis

    // Zkontrolujeme, zda se soubor otevřel správně
    if (!outFile) {
        std::cerr << "Chyba při otevírání souboru: " << jmeno_souboru << std::endl;
        return;

    }

    // Zapisujeme řetězec do souboru
    outFile << obsah;

    // Zavřeme soubor
    outFile.close();
    std::cout << "Data byla úspěšně uložena do souboru: " << jmeno_souboru << std::endl;
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