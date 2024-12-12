#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// Funkce pro otevření souboru
string otevri_soubor(const string& nazev_souboru) 
{
    ifstream inputFile(nazev_souboru);
    if (!inputFile) {
        cerr << "Nepodařilo se otevřít soubor." << endl;
        return "";
    }
    string obsah((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();
    return obsah;
}

// Funkce pro uložení do souboru
void uloz_do_souboru(const string& nazev_souboru, const string& obsah) 
{
    ofstream outputFile(nazev_souboru);
    if (!outputFile) {
        cerr << "Nepodařilo se vytvořit výstupní soubor." << endl;
        return;
    }
    outputFile << obsah;
    outputFile.close();
}

// Caesarova šifra
string caesar_sifra(string text, int shift, bool encrypt) 
{
    string result = "";
    for (char& c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + (encrypt ? shift : 26 - shift)) % 26 + base;
        }
        result += c;
    }
    return result;
}

// XOR šifra
string xor_sifra(string text, string key, bool encrypt) 
{
    string result = "";
    int keyLength = key.length();
    for (size_t i = 0; i < text.length(); ++i) {
        result += text[i] ^ key[i % keyLength];
    }
    return result;
}

// Vigenérova šifra
string vigener_sifra(string text, string key, bool encrypt) 
{
    string result = "";
    int keyIndex = 0;
    for (char& c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            char keyChar = islower(key[keyIndex % key.length()]) ? 'a' : 'A';
            if (encrypt) {
                c = (c - base + (key[keyIndex % key.length()] - keyChar)) % 26 + base;
            } else {
                c = (c - base - (key[keyIndex % key.length()] - keyChar) + 26) % 26 + base;
            }
            keyIndex++;
        }
        result += c;
    }
    return result;
}

// Playfairova šifra: Předzpracování textu (zbavení se háčků, čárek apod.)
string preprocessPlayfair(string text) 
{
    string preprocessed;
    for (char& c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            preprocessed += c;
        }
    }
    return preprocessed;
}

// Playfairova šifra: Generování čtverce
vector<vector<char>> generatePlayfairSquare(string key) 
{
    key = preprocessPlayfair(key);
    vector<vector<char>> square(5, vector<char>(5, ' '));
    map<char, bool> used;
    int row = 0, col = 0;
    for (char& c : key) {
        if (!used[c]) {
            square[row][col++] = c;
            used[c] = true;
            if (col == 5) { col = 0; row++; }
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!used[c]) {
            square[row][col++] = c;
            used[c] = true;
            if (col == 5) { col = 0; row++; }
        }
    }
    return square;
}

// Playfairova šifra: Šifrování a dešifrování
string playfairCipher(string text, string key, bool encrypt) 
{
    string preprocessed = preprocessPlayfair(text);
    if (encrypt && preprocessed.length() % 2 != 0) {
        preprocessed += 'X';
    }

    vector<vector<char>> square = generatePlayfairSquare(key);
    map<char, pair<int, int>> positions;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            positions[square[i][j]] = {i, j};
        }
    }

    string result = "";
    for (size_t i = 0; i < preprocessed.length(); i += 2) {
        char a = preprocessed[i];
        char b = preprocessed[i + 1];
        if (a == b && encrypt) b = 'X';
        
        int row1 = positions[a].first, col1 = positions[a].second;
        int row2 = positions[b].first, col2 = positions[b].second;

        if (row1 == row2) {
            result += square[row1][(col1 + (encrypt ? 1 : 4)) % 5];
            result += square[row2][(col2 + (encrypt ? 1 : 4)) % 5];
        } else if (col1 == col2) {
            result += square[(row1 + (encrypt ? 1 : 4)) % 5][col1];
            result += square[(row2 + (encrypt ? 1 : 4)) % 5][col2];
        } else {
            result += square[row1][col2];
            result += square[row2][col1];
        }
    }

    if (!encrypt && result.back() == 'X') {
        result.pop_back();
    }

    return result;
}

#ifndef __TEST__ // Add this preprocessor guard
//hlavní funkce
int main() 
{
    int action;
    cout << "Zadejte:\n1 pro šifrování \n2 pro dešifrování (pro první dešifrování je nutné zprávu už mít zašifrovanou)\n";
    cin >> action;

    string filePath = (action == 1) ? "vstup.txt" : "zasifrovany_vstup.txt";
    string text = otevri_soubor(filePath);
    if (text.empty()) {
        return 1;
    }

    int choice;
    cout << "\nVyber šifru:\n1. Caesarova šifra\n2. XOR šifra\n3. Vigenérova šifra\n4. Playfairova šifra\n";
    cin >> choice;

    string resultText;
    switch (choice) 
    {
        case 1: 
        {
            int shift;
            cout << "Zadej číselný posun pro Caesarovu šifru: ";
            cin >> shift;
            resultText = caesar_sifra(text, shift, action == 1);
            break;
        }

        case 2:
        {
            string key;
            cout << "Zadej binární klíč pro XOR šifru: ";
            cin >> key;
            resultText = xor_sifra(text, key, action == 1);
            break;
        }

        case 3: 
        {
            string key;
            cout << "Zadej slovní klíč pro Vigenérovu šifru: ";
            cin >> key;
            resultText = vigener_sifra(text, key, action == 1);
            break;
        }
        
        case 4:
        {
            string key;
            cout << "Zadej slovní klíč pro Playfairovu šifru: ";
            cin >> key;
            resultText = playfairCipher(text, key, action == 1);
            break;
        }
        default:
            cout << "Neplatná volba." << endl;
            return 1;
    }

    string outputPath = (action == 1) ? "zasifrovany_vstup.txt" : "desifrovany_vstup.txt";
    uloz_do_souboru(outputPath, resultText);

    cout << "Text byl " << ((action == 1) ? "zašifrován" : "dešifrován") << " a uložen do souboru " << outputPath << endl;
    return 0;
}
#endif // __TEST__