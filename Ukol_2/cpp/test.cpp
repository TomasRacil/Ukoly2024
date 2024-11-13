#include "gtest/gtest.h"
#include "sifry.cpp" // Předpokládám, že kód je v souboru vypocty.cpp

TEST(SifrovaciAlgoritmyTest, OtevriSoubor)
{
    std::string ocekavany_obsah = "Toto je tajna zprava!";
    std::string obsah_souboru = otevri_soubor("../vstup.txt");
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
    ASSERT_EQ(caesar_sifra(text, 5, true), "fmto");
    ASSERT_EQ(caesar_sifra(text, 25, true), "zgni");

    // Testy dešifrování
    ASSERT_EQ(caesar_sifra("dkrm", 3, false), text);
    ASSERT_EQ(caesar_sifra("fmto", 5, false), text);
    ASSERT_EQ(caesar_sifra("zgni", 25, false), text);
}

TEST(SifrovaciAlgoritmyTest, VigenerSifra)
{
    std::string text = "ahoj";
    // Testy s různými klíči
    ASSERT_EQ(vigener_sifra(text, "tajny", true), "thxw");
    ASSERT_EQ(vigener_sifra(text, "heslo", true), "hlgu");
    ASSERT_EQ(vigener_sifra(text, "klic", true), "kswl");

    // Testy dešifrování
    ASSERT_EQ(vigener_sifra("thxw", "tajny", false), text);
    ASSERT_EQ(vigener_sifra("hlgu", "heslo", false), text);
    ASSERT_EQ(vigener_sifra("kswl", "klic", false), text);
}

TEST(SifrovaciAlgoritmyTest, XORSifra)
{
    std::string text = "ahoj";
    // Testy s různými klíči
    ASSERT_EQ(xor_sifra(text, "tajny", true), "\025\t\005\004");
    ASSERT_EQ(xor_sifra(text, "heslo", true), "\t\r\034\006");
    ASSERT_EQ(xor_sifra(text, "klic", true), "\n\004\006\t");

    // Testy dešifrování
    ASSERT_EQ(xor_sifra("\025\t\005\004", "tajny", false), text);
    ASSERT_EQ(xor_sifra("\t\r\034\006", "heslo", false), text);
    ASSERT_EQ(xor_sifra("\n\004\006\t", "klic", false), text);
}

TEST(SifrovaciAlgoritmyTest, UlozDoSouboru)
{
    std::string testovaci_text = "Testovaci text pro ulozeni";
    std::string jmeno_souboru = "test_ulozeni.txt";
    uloz_do_souboru(jmeno_souboru, testovaci_text);

    // Ověření, zda byl soubor vytvořen a obsahuje správný text
    std::ifstream soubor(jmeno_souboru);
    std::string obsah_souboru((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    ASSERT_EQ(obsah_souboru, testovaci_text);

    // Vyčištění - odstranění testovacího souboru
    remove(jmeno_souboru.c_str());
}