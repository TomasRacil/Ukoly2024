#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

std::string otevri_soubor(const std::string& jmeno_souboru) {
    std::ifstream soubor(jmeno_souboru);
    if (!soubor) {
        std::cerr << "Chyba: Soubor " << jmeno_souboru << " neexistuje." << std::endl;
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
}

std::string caesar_sifra(const std::string& text, int posun, bool sifrovat) {
    std::string vysledek;
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int offset = sifrovat ? posun : -posun;
            vysledek += (c - base + offset + 26) % 26 + base;
        } else {
            vysledek += c; 
        }
    }
    return vysledek;
}

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
        } else {
            vysledek += c; 
        }
    }
    return vysledek;
}

std::string text_na_bin(const std::string& text) {
    std::string bin;
    for (char c : text) {
        bin += std::bitset<8>(static_cast<unsigned char>(c)).to_string();
    }
    return bin;
}

std::string bin_na_text(const std::string& bin) {
    std::string text;
    for (size_t i = 0; i < bin.length(); i += 8) {
        std::bitset<8> b(bin.substr(i, 8));
        text += static_cast<char>(b.to_ulong());
    }
    return text;
}

std::string xor_sifra(const std::string& text, const std::string& klic, bool sifrovat = true) {
    std::string vysledek;
    for (size_t i = 0; i < text.length(); ++i) {
        vysledek += text[i] ^ klic[i % klic.length()];
    }
    return vysledek;
}

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
    std::string vstupni_text = otevri_soubor("vstup.txt");

    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Caesarova šifra: " << sifrovany_text_caesar << std::endl;

    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << "Vigenerova šifra: " << sifrovany_text_vigener << std::endl;

    std::string binarni_text = text_na_bin(vstupni_text);
    std::cout << "Binární text: " << binarni_text << std::endl;

    std::string sifrovany_binarni = xor_sifra(binarni_text, "heslo", true);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_binarni);

    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);

    std::cout << "Dešifrovany text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
    std::cout << "Dešifrovany text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
    std::cout << "Dešifrovany text pomocí XOR šifry: " << bin_na_text(xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", true)) << std::endl;

    return 0;
}
#endif // __TEST__
