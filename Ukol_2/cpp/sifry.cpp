#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string& jmeno_souboru) {
    std::ifstream soubor(jmeno_souboru);
    if (!soubor) {
        std::cerr << "Chyba: Soubor " << jmeno_souboru << " neexistuje." << std::endl;
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string& text, int posun, bool sifrovat) {
    std::string vysledek;
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int offset = sifrovat ? posun : -posun;
            vysledek += (c - base + offset + 26) % 26 + base;
        }
        else {
            vysledek += c; 
        }
    }
    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string& text, const std::string& klic, bool sifrovat) {
    std::string vysledek;
    int klic_len = klic.length();
    for (size_t i = 0, j = 0; i < text.length(); ++i) {
        char c = text[i];
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int offset = sifrovat ? (tolower(klic[j % klic_len]) - 'a') : -(tolower(klic[j % klic_len]) - 'a');
            vysledek += (c - base + offset + 26) % 26 + base;
            j++;
        }
        else {
            vysledek += c; 
        }
    }
    return vysledek;
}

// Funkce pro převod textu na binární řetězec
std::string text_na_bin(const std::string& text) {
    std::string bin;
    for (char c : text) {
        bin += std::bitset<8>(static_cast<unsigned char>(c)).to_string();
    }
    return bin;
}

// Funkce pro převod binárního řetězce na text
std::string bin_na_text(const std::string& bin) {
    std::string text;
    for (size_t i = 0; i < bin.length(); i += 8) {
        std::bitset<8> b(bin.substr(i, 8));
        text += static_cast<char>(b.to_ulong());
    }
    return text;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string& text, const std::string& klic) {
    std::string vysledek;
    for (size_t i = 0; i < text.length(); ++i) {
        vysledek += text[i] ^ klic[i % klic.length()];
    }
    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string& jmeno_souboru, const std::string& obsah) {
    std::ofstream soubor(jmeno_souboru);
    if (!soubor) {
        std::cerr << "Chyba: Nelze uložit do souboru " << jmeno_souboru << "." << std::endl;
        return;
    }
    soubor << obsah;
}

#ifndef __TEST__ 
int main() {
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Caesarova šifra: " << sifrovany_text_caesar << std::endl;

    // Šifrování textu pomocí Vigenerovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << "Vigenerova šifra: " << sifrovany_text_vigener << std::endl;

    // Převod textu na binární formát
    std::string binarni_text = text_na_bin(vstupni_text);
    std::cout << "XOR šifra: " << binarni_text << std::endl;

    // Šifrování pomocí XOR
    std::string sifrovany_binarni = xor_sifra(binarni_text, "heslo");
    //std::cout << "Sifrovany binarni text: " << sifrovany_binarni << std::endl;

    // Uložení šifrovaných textů do souborů
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_binarni);

    // Dešifrování textů
    std::cout << "Dešifrovany text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
    std::cout << "Dešifrovany text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
    std::cout << "Dešifrovany text pomocí XOR šifry: " << bin_na_text(xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo")) << std::endl;

    return 0;
}
#endif // __TEST__
