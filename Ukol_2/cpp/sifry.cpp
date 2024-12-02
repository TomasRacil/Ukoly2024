#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <cctype>

using namespace std;

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru)
{
    std::ifstream soubor_vstup(jmeno_souboru);
    if (!soubor_vstup.is_open())
    {
        return "";
    }
    std::stringstream buffer;
    buffer << soubor_vstup.rdbuf();
    return buffer.str();
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat)
{
    std::string result;
    int actualShift = sifrovat ? posun : -posun;
    for (char ch : text)
    {
        if (std::isupper(ch))
        {
            result += (ch - 'A' + actualShift + 26) % 26 + 'A';
        }
        else if (std::islower(ch))
        {
            result += (ch - 'a' + actualShift + 26) % 26 + 'a';
        }
        else
        {
            result += ch;
        }
    }
    return result;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    std::string result;
    size_t keyIndex = 0;
    int keyLength = klic.length();
    if (keyLength == 0)
        throw std::invalid_argument("Klíč nesmí být prázdný.");
    for (char ch : text)
    {
        if (std::isalpha(ch))
        {
            char base = std::isupper(ch) ? 'A' : 'a';
            int shift = (toupper(klic[keyIndex]) - 'A') * (sifrovat ? 1 : -1);
            result += (ch - base + shift + 26) % 26 + base;
            keyIndex = (keyIndex + 1) % keyLength;
        }
        else
        {
            result += ch;
        }
    }
    return result;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat)
{
    if (klic.empty())
        throw std::invalid_argument("Klíč nesmí být prázdný.");
    std::string result;
    for (size_t i = 0; i < text.size(); ++i)
    {
        result += text[i] ^ klic[i % klic.size()];
    }
    return result;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah)
{
    std::ofstream outFile(jmeno_souboru);
    if (!outFile)
    {
        std::cerr << "Chyba při otevírání souboru: " << jmeno_souboru << std::endl;
        return;
    }
    outFile << obsah;
    outFile.close();
}
