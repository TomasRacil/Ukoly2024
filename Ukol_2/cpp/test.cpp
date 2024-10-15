#include "gtest/gtest.h"
#include "sifry.cpp" // Předpokládám, že kód je v souboru vypocty.cpp

TEST(SifrovaciAlgoritmyTest, OtevriSoubor)
{
    std::string ocekavany_obsah = "Toto je tajná zpráva!\n";
    std::string obsah_souboru = otevri_soubor("vstup.txt");
    ASSERT_EQ(obsah_souboru, ocekavany_obsah);
}

TEST(SifrovaciAlgoritmyTest, OtevriSouborNeexistujici)
{
    std::string obsah_souboru = otevri_soubor("neexistujici_soubor.txt");
    ASSERT_TRUE(obsah_souboru.empty()); // Očekáváme prázdný řetězec, pokud soubor neexistuje
}

TEST(SifrovaciAlgoritmyTest, CaesarSifra)
{
    std::string text = "ahoj";
    // Testy s různými posuny
    ASSERT_EQ(caesar_sifra(text, 1, true), "bipk");
    ASSERT_EQ(caesar_sifra(text, 5, true), "eptl");
    ASSERT_EQ(caesar_sifra(text, 25, true), "zgnr");

    // Testy dešifrování
    ASSERT_EQ(caesar_sifra("dkrm", 3, false), text);
    ASSERT_EQ(caesar_sifra("eptl", 5, false), text);
    ASSERT_EQ(caesar_sifra("zgnr", 25, false), text);
}

TEST(SifrovaciAlgoritmyTest, VigenerSifra)
{
    std::string text = "ahoj";
    // Testy s různými klíči
    ASSERT_EQ(vigener_sifra(text, "tajny", true), "kftm");
    ASSERT_EQ(vigener_sifra(text, "heslo", true), "lbuq");
    ASSERT_EQ(vigener_sifra(text, "klic", true), "ljub");

    // Testy dešifrování
    ASSERT_EQ(vigener_sifra("kftm", "tajny", false), text);
    ASSERT_EQ(vigener_sifra("lbuq", "heslo", false), text);
    ASSERT_EQ(vigener_sifra("ljub", "klic", false), text);
}

TEST(SifrovaciAlgoritmyTest, XORSifra)
{
    std::string text = "ahoj";
    // Testy s různými klíči
    ASSERT_EQ(xor_sifra(text, "tajny", true), "\x06\x1d\x1a\x0b");
    ASSERT_EQ(xor_sifra(text, "heslo", true), "\x02\x1b\x16\x0d");
    ASSERT_EQ(xor_sifra(text, "klic", true), "\x02\x1b\x16\x0d");

    // Testy dešifrování
    ASSERT_EQ(xor_sifra("\x06\x1d\x1a\x0b", "tajny", false), text);
    ASSERT_EQ(xor_sifra("\x02\x1b\x16\x0d", "heslo", false), text);
    ASSERT_EQ(xor_sifra("\x02\x1b\x16\x0d", "klic", false), text);
}

TEST(SifrovaciAlgoritmyTest, UlozDoSouboru)
{
    std::string testovaci_text = "Testovací text pro uložení";
    std::string jmeno_souboru = "test_ulozeni.txt";
    uloz_do_souboru(jmeno_souboru, testovaci_text);

    // Ověření, zda byl soubor vytvořen a obsahuje správný text
    std::ifstream soubor(jmeno_souboru);
    std::string obsah_souboru((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    ASSERT_EQ(obsah_souboru, testovaci_text);

    // Vyčištění - odstranění testovacího souboru
    remove(jmeno_souboru.c_str());
}