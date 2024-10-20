#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#ifdef _WIN32
#include <windows.h> // Windows-specific header for setting UTF-8 in the console
#endif

// Mapa pro nahrazení diakritiky - optimalizace pomocí statického pole
wchar_t diakriticke_mapovani[128] = {};

// Funkce pro naplnění mapy diakritických znaků
void napln_diakriticke_mapovani() {
    diakriticke_mapovani[L'á'] = L'a'; diakriticke_mapovani[L'č'] = L'c';
    diakriticke_mapovani[L'ď'] = L'd'; diakriticke_mapovani[L'é'] = L'e';
    diakriticke_mapovani[L'ě'] = L'e'; diakriticke_mapovani[L'í'] = L'i';
    diakriticke_mapovani[L'ň'] = L'n'; diakriticke_mapovani[L'ó'] = L'o';
    diakriticke_mapovani[L'ř'] = L'r'; diakriticke_mapovani[L'š'] = L's';
    diakriticke_mapovani[L'ť'] = L't'; diakriticke_mapovani[L'ú'] = L'u';
    diakriticke_mapovani[L'ů'] = L'u'; diakriticke_mapovani[L'ý'] = L'y';
    diakriticke_mapovani[L'ž'] = L'z'; diakriticke_mapovani[L'Á'] = L'A';
    diakriticke_mapovani[L'Č'] = L'C'; diakriticke_mapovani[L'Ď'] = L'D';
    diakriticke_mapovani[L'É'] = L'E'; diakriticke_mapovani[L'Ě'] = L'E';
    diakriticke_mapovani[L'Í'] = L'I'; diakriticke_mapovani[L'Ň'] = L'N';
    diakriticke_mapovani[L'Ó'] = L'O'; diakriticke_mapovani[L'Ř'] = L'R';
    diakriticke_mapovani[L'Š'] = L'S'; diakriticke_mapovani[L'Ť'] = L'T';
    diakriticke_mapovani[L'Ú'] = L'U'; diakriticke_mapovani[L'Ů'] = L'U';
    diakriticke_mapovani[L'Ý'] = L'Y'; diakriticke_mapovani[L'Ž'] = L'Z';
}

// Funkce pro odstranění diakritiky (in-place, bez kopírování řetězce)
void odstran_diakritiku_inplace(std::wstring &text) {
    for (size_t i = 0; i < text.size(); ++i) {
        wchar_t nahradit = diakriticke_mapovani[text[i]];
        if (nahradit) {
            text[i] = nahradit;
        }
    }
}

// Funkce pro Caesarovu šifru
std::wstring caesar_sifra(const std::wstring &text, int posun, bool sifrovat)
{
    std::wstring vysledek = text;
    if (!sifrovat)
    {
        posun = -posun; // Pokud dešifrujeme, posuneme zpět
    }
    for (wchar_t &znak : vysledek)
    {
        if (znak >= L'a' && znak <= L'z')
        {
            znak = L'a' + (znak - L'a' + posun + 26) % 26;
        }
        else if (znak >= L'A' && znak <= L'Z')
        {
            znak = L'A' + (znak - L'A' + posun + 26) % 26;
        }
    }
    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::wstring vigener_sifra(const std::wstring &text, const std::wstring &klic, bool sifrovat)
{
    std::wstring vysledek = text;
    int delka_klice = klic.size();
    for (size_t i = 0; i < text.size(); ++i)
    {
        wchar_t znak = text[i];
        if (znak >= L'a' && znak <= L'z')
        {
            int posun = (klic[i % delka_klice] - L'a') * (sifrovat ? 1 : -1);
            znak = L'a' + (znak - L'a' + posun + 26) % 26;
        }
        else if (znak >= L'A' && znak <= L'Z')
        {
            int posun = (klic[i % delka_klice] - L'A') * (sifrovat ? 1 : -1);
            znak = L'A' + (znak - L'A' + posun + 26) % 26;
        }
        vysledek[i] = znak;
    }
    return vysledek;
}

// Funkce pro XOR šifru
std::wstring xor_sifra(const std::wstring &text, const std::wstring &klic, bool sifrovat)
{
    std::wstring vysledek = text;
    int delka_klice = klic.size();
    for (size_t i = 0; i < text.size(); ++i)
    {
        vysledek[i] = text[i] ^ klic[i % delka_klice];
    }
    return vysledek;
}

// Funkce pro vytvoření matice Playfairovy šifry
void vytvor_playfair_matici(const std::wstring &klic, wchar_t matici[5][5], std::unordered_map<wchar_t, std::pair<int, int>> &pozice) {
    std::wstring bez_duplikatu;
    std::unordered_map<wchar_t, bool> navstiveno;

    // Přidání písmen z klíče do bez_duplikatu
    for (wchar_t znak : klic) {
        if (navstiveno[znak] == false && znak != L'J') { // V Playfairově šifře se 'J' považuje za 'I'
            navstiveno[znak] = true;
            bez_duplikatu += znak;
        }
    }

    // Přidání zbylých písmen abecedy
    for (wchar_t i = L'a'; i <= L'z'; ++i) {
        if (i != L'j' && navstiveno[i] == false) {
            navstiveno[i] = true;
            bez_duplikatu += i;
        }
    }

    // Naplnění matice
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            matici[i][j] = bez_duplikatu[i * 5 + j];
            pozice[matici[i][j]] = {i, j};
        }
    }
}

// Funkce pro vytvoření dvojic pro Playfairovu šifru
std::wstring vytvor_dvojice(const std::wstring &text) {
    std::wstring dvojice;
    for (size_t i = 0; i < text.length(); i += 2) {
        wchar_t prvni = text[i];
        wchar_t druhy = (i + 1 < text.length()) ? text[i + 1] : L'x'; // Pokud je lichý počet znaků, přidá 'x'
        if (prvni == druhy) {
            dvojice += prvni;
            dvojice += L'x'; // Pokud jsou znaky stejné, přidá 'x'
            i--; // Ovládání posunu pro další iteraci
        } else {
            dvojice += prvni;
            dvojice += druhy;
        }
    }
    return dvojice;
}

// Funkce pro šifrování textu pomocí Playfairovy šifry
std::wstring playfair_sifra(const std::wstring &text, const std::wstring &klic, bool sifrovat) {
    wchar_t matici[5][5];
    std::unordered_map<wchar_t, std::pair<int, int>> pozice;
    vytvor_playfair_matici(klic, matici, pozice);

    std::wstring dvojice = vytvor_dvojice(text);
    std::wstring vysledek;

    for (size_t i = 0; i < dvojice.length(); i += 2) {
        wchar_t prvni = dvojice[i];
        wchar_t druhy = dvojice[i + 1];

        auto [x1, y1] = pozice[prvni];
        auto [x2, y2] = pozice[druhy];

        if (x1 == x2) { // Ve stejném řádku
            if (sifrovat) {
                vysledek += matici[x1][(y1 + 1) % 5];
                vysledek += matici[x2][(y2 + 1) % 5];
            } else {
                vysledek += matici[x1][(y1 + 4) % 5]; // Dešifrování
                vysledek += matici[x2][(y2 + 4) % 5];
            }
        } else if (y1 == y2) { // Ve stejném sloupci
            if (sifrovat) {
                vysledek += matici[(x1 + 1) % 5][y1];
                vysledek += matici[(x2 + 1) % 5][y2];
            } else {
                vysledek += matici[(x1 + 4) % 5][y1]; // Dešifrování
                vysledek += matici[(x2 + 4) % 5][y2];
            }
        } else { // V obdélníku
            vysledek += matici[x1][y2];
            vysledek += matici[x2][y1];
        }
    }
    return vysledek;
}

// Funkce pro otevření souboru a načtení jeho obsahu s použitím UTF-8
std::wstring otevri_soubor(const std::wstring &jmeno_souboru)
{
    std::wifstream soubor(jmeno_souboru.c_str());
    soubor.imbue(std::locale(""));

    if (!soubor.is_open())
    {
        std::wcerr << L"Chyba pri otevirani souboru: " << jmeno_souboru << std::endl;
        return L"";
    }

    std::wstring obsah((std::istreambuf_iterator<wchar_t>(soubor)), std::istreambuf_iterator<wchar_t>());
    soubor.close();
    return obsah;
}

// Funkce pro uložení textu do souboru s použitím UTF-8
void uloz_soubor(const std::wstring &jmeno_souboru, const std::wstring &text)
{
    std::wofstream soubor(jmeno_souboru.c_str());
    soubor.imbue(std::locale(""));

    if (!soubor.is_open())
    {
        std::wcerr << L"Chyba pri ukladani souboru: " << jmeno_souboru << std::endl;
        return;
    }

    soubor << text;
    soubor.close();
}

#ifndef __TEST__ // Přepínač pro testování
int main() {
    // Windows: Nastavení výstupu na UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    napln_diakriticke_mapovani(); // Inicializace mapování diakritiky

    std::wstring vstupni_text;
    wchar_t volba;

    // Dotaz na uživatele, zda chce načíst text ze souboru nebo ho zadat ručně
    std::wcout << L"Chcete nacist text ze souboru (S) nebo ho zadat do konzole (K)? (S/K): ";
    std::wcin >> volba;
    std::wcin.ignore();

    if (volba == L'S' || volba == L's') {
        std::wstring jmeno_souboru;
        std::wcout << L"Zadejte nazev souboru: ";
        std::getline(std::wcin, jmeno_souboru);
        vstupni_text = otevri_soubor(jmeno_souboru);
    } else if (volba == L'K' || volba == L'k') {
        std::wcout << L"Zadejte text pro sifrovani: ";
        std::getline(std::wcin, vstupni_text);
    } else {
        std::wcerr << L"Neplatna volba!" << std::endl;
        return 1;
    }

    // Odstranění diakritiky
    odstran_diakritiku_inplace(vstupni_text);
    std::wcout << L"Text po odstraneni diakritiky: " << vstupni_text << std::endl;

    // Nabídka šifer
    std::wcout << L"Zvolte sifru (C - Caesar, V - Vigenere, X - XOR, P - Playfair): ";
    std::wcin >> volba;
    std::wcin.ignore();

    if (volba == L'C' || volba == L'c') {
        int posun;
        std::wcout << L"Zadejte posun pro Caesarovu sifru: ";
        std::wcin >> posun;
        vstupni_text = caesar_sifra(vstupni_text, posun, true);
    } else if (volba == L'V' || volba == L'v') {
        std::wstring klic;
        std::wcout << L"Zadejte klic pro Vigenerovu sifru: ";
        std::wcin >> klic;
        vstupni_text = vigener_sifra(vstupni_text, klic, true);
    } else if (volba == L'X' || volba == L'x') {
        std::wstring klic;
        std::wcout << L"Zadejte klic pro XOR sifru: ";
        std::wcin >> klic;
        vstupni_text = xor_sifra(vstupni_text, klic, true);
    } else if (volba == L'P' || volba == L'p') {
        std::wstring klic;
        std::wcout << L"Zadejte klic pro Playfair sifru: ";
        std::wcin >> klic;
        vstupni_text = playfair_sifra(vstupni_text, klic, true);
    } else {
        std::wcerr << L"Neplatna volba!" << std::endl;
        return 1;
    }

    std::wcout << L"Zasifrovany text: " << vstupni_text << std::endl;

    // Možnost uložení do souboru
    std::wcout << L"Prejete si ulozit text do souboru? (A/N): ";
    std::wcin >> volba;
    if (volba == L'A' || volba == L'a') {
        std::wstring jmeno_souboru;
        std::wcout << L"Zadejte nazev souboru: ";
        std::wcin.ignore();
        std::getline(std::wcin, jmeno_souboru);
        uloz_soubor(jmeno_souboru, vstupni_text);
    }

    return 0;
}
#endif
