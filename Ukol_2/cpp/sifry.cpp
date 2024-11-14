
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// XOR šifra
string xor_sifra(const string& text, const string& klic) {
    string vysledek;
    size_t delkaKlice = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        vysledek += text[i] ^ klic[i % delkaKlice]; // XOR operace
    }

    return vysledek;
}

// Caesarova šifra (posun je klíč)
string caesar_sifra(const string& text, int posun, bool sifrovat) {
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
string vigener_sifra(const string& text, const string& klic, bool sifrovat) {
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

// Načtení obsahu ze souboru
string otevri_soubor(const string& nazevSouboru) {
    ifstream soubor(nazevSouboru);
    if (!soubor.is_open()) {
        cerr << "Soubor nelze otevrit: " << nazevSouboru << endl;
        return "";
    }

    string obsah;
    string radek;
    while (getline(soubor, radek)) {
        obsah += radek + "\n";
    }

    soubor.close();
    return obsah;
}

// Uložení obsahu do souboru
void uloz_do_souboru(const string& nazevSouboru, const string& obsah) {
    ofstream soubor(nazevSouboru);
    if (!soubor.is_open()) {
        cerr << "Soubor nelze otevrit pro zapis: " << nazevSouboru << endl;
        return;
    }

    soubor << obsah;
    soubor.close();
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

 
    string obsah = otevri_soubor(vstupniSoubor);
    if (obsah.empty()) {
        cerr << "Chyba pri nacitani souboru." << endl;
        return 1;
    }

    string vyslednyText;
    if (volbaSifry == 'x') {
        vyslednyText = xor_sifra(obsah, klic);
    } else if (volbaSifry == 'c') {
        vyslednyText = caesar_sifra(obsah, posun, sifrovat);
    } else if (volbaSifry == 'v') {
        vyslednyText = vigener_sifra(obsah, klic, sifrovat);
    }

    uloz_do_souboru(vystupniSoubor, vyslednyText);

    if (sifrovat) {
        cout << "Text byl zasifrovan a ulozen do: " << vystupniSoubor << endl;
    } else {
        cout << "Text byl desifrovan a ulozen do: " << vystupniSoubor << endl;
    }

    return 0;
}