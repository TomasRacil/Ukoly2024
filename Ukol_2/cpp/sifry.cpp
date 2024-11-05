#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <locale>
#include <codecvt>

// Mapa pro odstranění diakritiky
wchar_t diakriticke_mapovani[128] = {};

// Funkce pro naplnění mapy diakritiky
void napln_diakriticke_mapovani() {
    std::unordered_map<wchar_t, wchar_t> diakriticka_mapa = {
            {L'á', L'a'}, {L'č', L'c'}, {L'ď', L'd'}, {L'é', L'e'}, {L'ě', L'e'},
            {L'í', L'i'}, {L'ň', L'n'}, {L'ó', L'o'}, {L'ř', L'r'}, {L'š', L's'},
            {L'ť', L't'}, {L'ú', L'u'}, {L'ů', L'u'}, {L'ý', L'y'}, {L'ž', L'z'},
            {L'Á', L'A'}, {L'Č', L'C'}, {L'Ď', L'D'}, {L'É', L'E'}, {L'Ě', L'E'},
            {L'Í', L'I'}, {L'Ň', L'N'}, {L'Ó', L'O'}, {L'Ř', L'R'}, {L'Š', L'S'},
            {L'Ť', L'T'}, {L'Ú', L'U'}, {L'Ů', L'U'}, {L'Ý', L'Y'}, {L'Ž', L'Z'}
    };
    for (const auto& pair : diakriticka_mapa)
        diakriticke_mapovani[pair.first] = pair.second;
}

// Funkce pro odstranění diakritiky (in-place)
void odstran_diakritiku_inplace(std::wstring &text) {
    for (wchar_t& znak : text)
        if (diakriticke_mapovani[znak])
            znak = diakriticke_mapovani[znak];
}

// Caesarova šifra
std::wstring caesar_sifra(const std::wstring &text, int posun, bool sifrovat) {
    std::wstring vysledek = text;
    posun = sifrovat ? posun : -posun;
    for (wchar_t &znak : vysledek) {
        if (znak >= L'a' && znak <= L'z')
            znak = L'a' + (znak - L'a' + posun + 26) % 26;
        else if (znak >= L'A' && znak <= L'Z')
            znak = L'A' + (znak - L'A' + posun + 26) % 26;
    }
    return vysledek;
}

// Vigenereova šifra
std::wstring vigener_sifra(const std::wstring &text, const std::wstring &klic, bool sifrovat) {
    std::wstring vysledek = text;
    for (size_t i = 0; i < text.size(); ++i) {
        int posun = (klic[i % klic.size()] - (iswlower(klic[i % klic.size()]) ? L'a' : L'A')) * (sifrovat ? 1 : -1);
        wchar_t &znak = vysledek[i];
        if (znak >= L'a' && znak <= L'z')
            znak = L'a' + (znak - L'a' + posun + 26) % 26;
        else if (znak >= L'A' && znak <= L'Z')
            znak = L'A' + (znak - L'A' + posun + 26) % 26;
    }
    return vysledek;
}

// XOR šifra
std::wstring xor_sifra(const std::wstring &text, const std::wstring &klic) {
    std::wstring vysledek = text;
    for (size_t i = 0; i < text.size(); ++i)
        vysledek[i] = text[i] ^ klic[i % klic.size()];
    return vysledek;
}

// Utility function to convert wstring to UTF-8 encoded string
std::string wstring_to_utf8(const std::wstring &wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

// Otevření souboru s UTF-8
std::wstring otevri_soubor(const std::wstring &jmeno_souboru) {
    std::ifstream soubor(wstring_to_utf8(jmeno_souboru), std::ios::binary);
    if (!soubor.is_open()) {
        std::wcerr << L"Chyba pri otevirani souboru: " << jmeno_souboru << std::endl;
        return L"";
    }
    std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(obsah);
}

// Uložení do souboru s UTF-8
void uloz_soubor(const std::wstring &jmeno_souboru, const std::wstring &text) {
    std::ofstream soubor(wstring_to_utf8(jmeno_souboru), std::ios::binary);
    if (!soubor.is_open())
        std::wcerr << L"Chyba pri ukladani souboru: " << jmeno_souboru << std::endl;
    else {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        soubor << conv.to_bytes(text);
    }
}

// Zpracování textu uživatele
std::wstring nacti_text_od_uzivatele() {
    std::wstring vstupni_text;
    wchar_t volba;
    std::wcout << L"Chcete nacist text ze souboru (S) nebo zadat do konzole (K)? (S/K): ";
    std::wcin >> volba;
    std::wcin.ignore();

    if (towupper(volba) == L'S') {
        std::wstring jmeno_souboru;
        std::wcout << L"Zadejte nazev souboru: ";
        std::getline(std::wcin, jmeno_souboru);
        return otevri_soubor(jmeno_souboru);
    } else {
        std::wcout << L"Zadejte text pro sifrovani: ";
        std::getline(std::wcin, vstupni_text);
    }
    return vstupni_text;
}

int main() {
    napln_diakriticke_mapovani();
    std::wstring text = nacti_text_od_uzivatele();
    odstran_diakritiku_inplace(text);
    std::wcout << L"Text po odstraneni diakritiky: " << text << std::endl;

    wchar_t volba;
    std::wcout << L"Zvolte sifru (C - Caesar, V - Vigenere, X - XOR): ";
    std::wcin >> volba;
    std::wcin.ignore();

    switch (towupper(volba)) {
        case L'C': {
            int posun;
            std::wcout << L"Zadejte posun pro Caesarovu sifru: ";
            std::wcin >> posun;
            text = caesar_sifra(text, posun, true);
            break;
        }
        case L'V': {
            std::wstring klic;
            std::wcout << L"Zadejte klíc pro Vigenerovu sifru: ";
            std::wcin >> klic;
            text = vigener_sifra(text, klic, true);
            break;
        }
        case L'X': {
            std::wstring klic;
            std::wcout << L"Zadejte klic pro XOR sifru: ";
            std::wcin >> klic;
            text = xor_sifra(text, klic);
            break;
        }
        default:
            std::wcerr << L"Neplatna volba." << std::endl;
            return 1;
    }
    uloz_soubor(L"zasifrovany_text.txt", text);
    std::wcout << L"Sifrovaný text byl ulozen do 'zasifrovany_text.txt'" << std::endl;
    return 0;
}
