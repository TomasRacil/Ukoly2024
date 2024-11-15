#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string& jmeno_souboru)
{
	// Implementace funkce pro otevření souboru a načtení jeho obsahu
	std::ifstream soubor(jmeno_souboru); 
	if (!soubor.is_open()) { 
		std::cerr << "Chyba: Soubor " << jmeno_souboru << " nelze otevřít." << std::endl;
		return ""; 
	}

	std::string obsah;
	std::string radek;
	while (std::getline(soubor, radek)) {
		obsah += radek; 
	}

	soubor.close(); 
	return obsah;
}

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string& text, int posun, bool sifrovat)
{
	std::string vysledek = "";
	int realny_posun = posun;

	if (!sifrovat) {
		realny_posun = -posun;
	}

	for (char znak : text) {
		if (isalpha(znak)) { 
			char zaklad = islower(znak) ? 'a' : 'A'; 
			znak = (znak - zaklad + realny_posun + 26) % 26 + zaklad;
		}
		vysledek += znak;
	}
	return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
	std::string vysledek = "";
	int delka_klice = klic.length();
	int posun;

	for (size_t i = 0; i < text.length(); ++i) {
		char znak = text[i];

		if (isalpha(znak)) {
			char znak_klice = klic[i % delka_klice];
			posun = tolower(znak_klice) - 'a'; 

			if (!sifrovat) {
				posun = -posun; 
			}

			if (islower(znak)) {
				znak = (znak - 'a' + posun + 26) % 26 + 'a';
			}
			else if (isupper(znak)) {
				znak = (znak - 'A' + posun + 26) % 26 + 'A';
			}
		}

		vysledek += znak;
	}

	return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string& text, const std::string& klic, bool /*sifrovat*/)
{
	std::string vysledek = "";
	int delka_klice = klic.length();

	for (size_t i = 0; i < text.length(); ++i) {
		char znak_klice = klic[i % delka_klice];
		vysledek += text[i] ^ znak_klice;
	}

	return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string& jmeno_souboru, const std::string& obsah)
{
	std::ofstream soubor(jmeno_souboru);

	if (!soubor.is_open()) {
		std::cerr << "Chyba: Soubor " << jmeno_souboru << " nelze otevřít." << std::endl;
		return;
	}

	soubor << obsah;
	soubor.close();

	std::cout << "Obsah byl úspěšně uložen do souboru: " << jmeno_souboru << std::endl;
}

// Hlavní funkce, která se spustí pouze, pokud není definováno makro __TEST__
#ifndef __TEST__
int main()
{
	std::string vstupni_text = otevri_soubor("vstup.txt");

	std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
	std::cout << sifrovany_text_caesar << std::endl;

	std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
	std::cout << sifrovany_text_vigener << std::endl;

	std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
	std::cout << sifrovany_text_xor << std::endl;

	uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
	uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
	uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

	std::cout << "Dešifrovany text pomocí Caesarovy šifry: " 
              << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
	std::cout << "Dešifrovany text pomocí Vigenerovy šifry: " 
              << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
	std::cout << "Dešifrovany text pomocí XOR šifry: " 
              << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

	return 0;
}
#endif // __TEST__


// TESETY	cd Ukol_2/cpp && mkdir -p build && cd build && cmake .. && make && ./mytests || exit 1
/*
-- Configuring done
-- Generating done
-- Build files have been written to: /workspaces/Ukoly2024/Ukol_2/cpp/build
Scanning dependencies of target mytests
[ 25%] Building CXX object CMakeFiles/mytests.dir/test.cpp.o
[ 50%] Linking CXX executable mytests
[ 50%] Built target mytests
Scanning dependencies of target sifry
[ 75%] Building CXX object CMakeFiles/sifry.dir/sifry.cpp.o
[100%] Linking CXX executable sifry
[100%] Built target sifry
Running main() from /build/googletest-YnT0O3/googletest-1.10.0.20201025/googletest/src/gtest_main.cc
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from SifrovaciAlgoritmyTest
[ RUN      ] SifrovaciAlgoritmyTest.OtevriSoubor
[       OK ] SifrovaciAlgoritmyTest.OtevriSoubor (0 ms)
[ RUN      ] SifrovaciAlgoritmyTest.OtevriSouborNeexistujici
Chyba: Soubor neexistujici_soubor.txt nelze otevřít.
[       OK ] SifrovaciAlgoritmyTest.OtevriSouborNeexistujici (0 ms)
[ RUN      ] SifrovaciAlgoritmyTest.CaesarSifra
[       OK ] SifrovaciAlgoritmyTest.CaesarSifra (0 ms)
[ RUN      ] SifrovaciAlgoritmyTest.VigenerSifra
[       OK ] SifrovaciAlgoritmyTest.VigenerSifra (0 ms)
[ RUN      ] SifrovaciAlgoritmyTest.XORSifra
[       OK ] SifrovaciAlgoritmyTest.XORSifra (0 ms)
[ RUN      ] SifrovaciAlgoritmyTest.UlozDoSouboru
Obsah byl úspěšně uložen do souboru: test_ulozeni.txt
[       OK ] SifrovaciAlgoritmyTest.UlozDoSouboru (0 ms)
[----------] 6 tests from SifrovaciAlgoritmyTest (1 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 6 tests.
*/