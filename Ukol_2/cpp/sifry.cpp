#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>

using namespace std;

string otevri_soubor(const string &jmeno_souboru) {
    ifstream file(jmeno_souboru);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file. Check the path." << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

string caesar_sifra(const string &text, int posun, bool sifrovat) {
    string vysledek = text;
    if (!sifrovat) posun = -posun;
    for (char &ch : vysledek) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = base + (ch - base + posun + 26) % 26;
        }
    }
    return vysledek;
}

string vigener_sifra(const string &text, const string &klic, bool sifrovat) {
    string vysledek;
    int klicDelka = klic.length();
    for (size_t i = 0; i < text.length(); i++) {
        char znak = text[i];
        char klicZnak = tolower(klic[i % klicDelka]) - 'a';
        if (isalpha(znak)) {
            char base = islower(znak) ? 'a' : 'A';
            if (sifrovat)
                znak = base + (znak - base + klicZnak) % 26;
            else
                znak = base + (znak - base - klicZnak + 26) % 26;
        }
        vysledek += znak;
    }
    return vysledek;
}

string xor_sifra(const string &text, const string &klic, bool sifrovat) {
    string vysledek;
    int klicDelka = klic.length();
    for (size_t i = 0; i < text.length(); i++) {
        vysledek += text[i] ^ klic[i % klicDelka];
    }
    return vysledek;
}

void uloz_do_souboru(const string &jmeno_souboru, const string &obsah) {
    ofstream file(jmeno_souboru);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file for writing!" << endl;
    } else {
        file << obsah;
        cout << "Data written to file " << jmeno_souboru << " successfully." << endl;
    }
}

#ifndef __TEST__
int main() {
    string vstupni_text = otevri_soubor("vstup.txt");
    
    string sifrovany_caesar = caesar_sifra(vstupni_text, 3, true);
    string sifrovany_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    string sifrovany_xor = xor_sifra(vstupni_text, "heslo", true);
    
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_xor);
    
    cout << "Dešifrovany text Caesar: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << endl;
    cout << "Dešifrovany text Vigener: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << endl;
    cout << "Dešifrovany text XOR: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << endl;
    
    return 0;
}
#endif
