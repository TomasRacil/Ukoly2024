#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string &jmeno_souboru) {
    // Implementace funkce pro otevření souboru a načtení jeho obsahu
    //otevření souboru
    std::ifstream soubor(jmeno_souboru);
    //pokud soubor neexistuje
    if (!soubor) {
        std::cerr << "Chyba: Soubor neexistuje " << jmeno_souboru << std::endl;
        //vrácení prázdného řetězce
        return "";
    }
    //pokud se soubor nepodaří otevřít
    if (!soubor) {
        std::cerr << "Chyba: Soubor nelze otevřít " << jmeno_souboru << std::endl;
        //vrácení prázdného řetězce
        return "";
    }
    //přečtení obsahu souboru, označí si začátek a konec (konec je ) souboru a poté si obsah souboru uloží do proměnné obsah
    std::string obsah = std::string((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
     if(obsah.empty()){
        std::cerr << "Chyba: Soubor je prázdný " << jmeno_souboru << std::endl;
    }
    //vrácení obsahu souboru
    return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string &text, int posun, bool sifrovat) {
    // Implementace Caesarovy šifry
    // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
    //pokud je posun větší než 26 tak se zadané číslo posune o zbytek po dělení 26
    posun = posun % 26;
    //pokud je posun záporný
    if (posun < 0) {
        //přičtení 26
        posun += 26;
    }
    //deklarace proměnné pro uložení výsledku
    std::string vysledek = "";
    //cyklus pro každý znak v textu
    for (int i = 0; i < text.length(); i++) {
        //uložení znaku
        char znak = text[i];
        //pokud je znak písmeno
        if (isalpha(znak)) {
            //pokud je znak velké písmeno
            if (isupper(znak)) {
                //šifrování
                if (sifrovat) {
                    znak = char((znak - 'A' + posun) % 26 + 'A'); //šifrování velkých písmen
                } else {
                    znak = char((znak - 'A' - posun + 26) % 26 + 'A'); //dešifrování velkých písmen
                }
            } else {
                if (sifrovat) {
                    znak = char((znak - 'a' + posun) % 26 + 'a'); //šifrování malých písmen
                } else {
                    znak = char((znak - 'a' - posun + 26) % 26 + 'a'); //dešifrování malých písmen
                }
            }


        }
        //přidání znaku do výsledku
        vysledek += znak;
    }
    //vrácení výsledku
    return vysledek;
}


// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
    // Implementace Vigenerovy šifry
    // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
    //deklarace proměnných
    std::string vysledek = "";
    int delka_klice = klic.length(); //délka klíče
    int delka_textu = text.length(); //délka textu
    //cyklus pro každý znak v textu
    for (int i = 0; i < delka_textu; i++) {
        //uložení znaku
        char znak = text[i]; //uložení znaku
        char klic_znak = klic[i % delka_klice]; //uložení znaku klíče
        //pokud je znak písmeno
        if (isalpha(znak)) {
            //pokud je znak velké písmeno
            if (isupper(znak)) {
                //šifrování
                if (sifrovat) {
                    znak = char((znak - 'A' + (klic_znak - 'A')) % 26 + 'A'); //šifrování velkých písmen
                } else {
                    znak = char((znak - 'A' - (klic_znak - 'A') + 26) % 26 + 'A'); //dešifrování velkých písmen
                }
            } else {
                if (sifrovat) {
                    znak = char((znak - 'a' + (klic_znak - 'a')) % 26 + 'a'); //šifrování malých písmen
                } else {
                    znak = char((znak - 'a' - (klic_znak - 'a') + 26) % 26 + 'a'); //dešifrování malých písmen
                }

            }
        }
        //přidání znaku do výsledku
        vysledek += znak;
    }
    //vrácení výsledku
    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string &text, const std::string &klic, bool sifrovat) {
    // Implementace XOR šifry
    // sifrovat = true pro šifrování, sifrovat = false pro dešifrování
    //deklarace proměnných
    std::string vysledek = "";
    int delka_klice = klic.length(); //délka klíče
    int delka_textu = text.length(); //délka textu

    for (int i = 0; i < delka_textu; i++) {
        char znak = text[i]; //uložení znaku
        znak = znak ^ klic[i % delka_klice]; //XOR operace je symetrická, takže ji můžeme použít pro šifrování i dešifrování
        vysledek += znak; //přidání znaku do výsledku
    }

    return vysledek;
}


// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string &jmeno_souboru, const std::string &obsah) {
    // Implementace funkce pro uložení řetězce do souboru
    //otevření souboru
    std::ofstream soubor(jmeno_souboru);
    if (!soubor) {
        std::cerr << "Chyba: Nelze Vytvorit soubor " << jmeno_souboru << std::endl; //pokud se soubor nepodaří vytvořit vypíše chybu
        return;
    }
    soubor << obsah;
    if (!soubor) {
        std::cerr << "Chyba: Nelze zapsat do souboru " << jmeno_souboru << std::endl; //pokud se nepodaří zapsat do souboru vypíše chybu
    }
    soubor.close();
}

#ifndef __TEST__ // Add this preprocessor guard

int main() {
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor(R"(vstup.txt)");

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << sifrovany_text_caesar << std::endl;

    // Šifrování textu pomocí Vigenerovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << sifrovany_text_vigener << std::endl;

    // Šifrování textu pomocí XOR šifry
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
    std::cout << sifrovany_text_xor << std::endl;

    // Uložení šifrovaných textů do souborůS
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

    // Dešifrování textů
    std::cout << "Dešifrovany text pomocí Caesarovy šifry: "
              << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
    std::cout << "Dešifrovany text pomocí Vigenerovy šifry: "
              << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
    std::cout << "Dešifrovany text pomocí XOR šifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false)
              << std::endl;


    return 0;
}

#endif // __TEST__
