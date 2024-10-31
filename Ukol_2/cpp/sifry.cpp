
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// XOR šifra
string xorSifra(const string& text, const string& klic) {
    string vysledek;
    size_t delkaKlice = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        vysledek += text[i] ^ klic[i % delkaKlice]; // XOR operace
    }

    return vysledek;
}

// Caesarova šifra (posun je klíč)
string caesarSifra(const string& text, int posun, bool sifrovat) {
    string vysledek;
    int skutecnyPosun = sifrovat ? posun : -posun; // Změna posunu pro dešifrování

    for (char znak : text) {
        if (isalpha(znak)) {
            char zaklad = isupper(znak) ? 'A' : 'a';
            znak = (znak - zaklad + skutecnyPosun + 26) % 26 + zaklad; // Posun a vypocet
        }
        vysledek += znak;
    }

    return vysledek;
}

// Vigenerova šifra
string vigenereSifra(const string& text, const string& klic, bool sifrovat) {
    string vysledek;
    size_t delkaKlice = klic.length();
    int posun;

    for (size_t i = 0; i < text.length(); ++i) {
        char znak = text[i];
        char klicZnak = klic[i % delkaKlice];

        if (isalpha(znak)) {
            // Určení posunu v závislosti na šifrování nebo dešifrování
            posun = sifrovat ? (klicZnak - 'a') : -(klicZnak - 'a');
            char zaklad = isupper(znak) ? 'A' : 'a';
            znak = (znak - zaklad + posun + 26) % 26 + zaklad; // Posun a vypocet
        }

        vysledek += znak;
    }

    return vysledek;
}

// Funkce pro práci se souborem
void pracujSeSouborem(const string& vstupniSoubor, const string& vystupniSoubor, const string& klic, int posun, bool sifrovat, char typSifry) {
    ifstream souborVstup(vstupniSoubor);
    if (!souborVstup.is_open()) {
        cerr << "Vstupni soubor nelze otevrit." << endl;
        return;
    }

    ofstream souborVystup(vystupniSoubor);
    if (!souborVystup.is_open()) {
        cerr << "Vystupni soubor nelze otevrit." << endl;
        return;
    }

    string radek;
    string vyslednyText;  

    // Načtení vstupního souboru a aplikace šifry dle výběru
    while (getline(souborVstup, radek)) {
        if (typSifry == 'x') {
            vyslednyText += xorSifra(radek, klic) + "\n";  // Volání XOR šifry
        }
        else if (typSifry == 'c') {
            vyslednyText += caesarSifra(radek, posun, sifrovat) + "\n";  // Volání Caesarovy šifry
        }
        else if (typSifry == 'v') {
            vyslednyText += vigenereSifra(radek, klic, sifrovat) + "\n";  // Volání Vigenerovy šifry
        }

    }

    // Zápis výsledku do výstupního souboru
    souborVystup << vyslednyText;

    souborVstup.close();
    souborVystup.close();
}

int main() {
    string vstupniSoubor = "vstup.txt";        // Název vstupního souboru
    string vystupniSoubor = "vystup.txt";      // Název výstupního souboru
    string klic;                               // Klíč pro šifry
    int posun = 0;                             // Posun pro Caesarovu šifru
    bool sifrovat;                             // Volba pro šifrování nebo dešifrování
    char volbaSifry;                           // Uživatel vybírá šifru (x = XOR, c = Caesar, v = Vigenere)
    char volbaAkce;                            // Uživatel vybírá šifrování nebo dešifrování

    // Výběr šifry
    cout << "Vyberte sifru (x = XOR, c = Caesarova, v = Vigenereova): ";
    cin >> volbaSifry;

    if (volbaSifry != 'x' && volbaSifry != 'c' && volbaSifry != 'v') {
        cerr << "Neplatna volba sifry!" << endl;
        return 1;
    }

    // Výběr mezi šifrováním nebo dešifrováním
    cout << "Vyberte (s = sifrovat, d = desifrovat): ";
    cin >> volbaAkce;

    if (volbaAkce == 's') {
        sifrovat = true;
        cout << "Zvoleno sifrovani" << endl;
    }
    else if (volbaAkce == 'd') {
        sifrovat = false;
        cout << "Zvoleno desifrovani" << endl;
    }
    else {
        cerr << "Neplatna akce" << endl;
        return 1;
    }

    // Zadani posunu v případě výběru Caesarovy šifry
    if (volbaSifry == 'c') {
        cout << "Zadejte posun pro Caesarovu sifru: ";
        cin >> posun;
    }

    // Zadani klíče v případě výběru XOR nebo Vigenerovy šifry
    if (volbaSifry == 'x' || volbaSifry == 'v') {
        cout << "Zadejte klic: ";
        cin >> klic;
    }

    // Práce se soubory a šifrování/dešifrování podle volby uživatele
    pracujSeSouborem(vstupniSoubor, vystupniSoubor, klic, posun, sifrovat, volbaSifry);

    if (sifrovat) {
        std::cout << "Text byl zasifrovan a ulozen do: " << vystupniSoubor << endl;
    }
    else {
        std::cout << "Text byl desifrovan a ulozen do: " << vystupniSoubor << endl;
    }

    return 0;
}