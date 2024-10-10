#include "gtest/gtest.h"
#include "vypocty.cpp" // Předpokládám, že kód je v souboru vypocty.cpp

TEST(TestyFunkci, Soucet)
{
    std::vector<int> cisla = {1, 2, 3};
    EXPECT_EQ(soucet(cisla), 6);

    cisla = {-1, 0, 1};
    EXPECT_EQ(soucet(cisla), 0);

    cisla = {1, 1, 1};
    EXPECT_EQ(soucet(cisla), 3);

    cisla = {}; // Prázdný seznam
    EXPECT_EQ(soucet(cisla), 0);
}

TEST(TestyFunkci, Soucin)
{
    std::vector<int> cisla = {1, 2, 3};
    EXPECT_EQ(soucin(cisla), 6);

    cisla = {-1, 2, 3};
    EXPECT_EQ(soucin(cisla), -6);

    cisla = {0, 2, 3};
    EXPECT_EQ(soucin(cisla), 0);

    cisla = {}; // Prázdný seznam
    EXPECT_EQ(soucin(cisla), 1);
}

TEST(TestyFunkci, Prumer)
{
    std::vector<int> cisla = {1, 2, 3};
    EXPECT_EQ(prumer(cisla), 2);

    cisla = {-1, 0, 1};
    EXPECT_EQ(prumer(cisla), 0);

    cisla = {1, 1, 1};
    EXPECT_EQ(prumer(cisla), 1);

    cisla = {}; // Prázdný seznam - zde by mohla funkce házet výjimku
    // EXPECT_THROW(prumer(cisla), std::exception); // Otestuj, zda je vyhozena výjimka
}

TEST(TestyFunkci, Median)
{
    std::vector<int> cisla = {1, 2, 3};
    EXPECT_EQ(median(cisla), 2);

    cisla = {1, 3, 2};
    EXPECT_EQ(median(cisla), 2);

    cisla = {1, 1, 2};
    EXPECT_EQ(median(cisla), 1);

    cisla = {1}; // Jeden prvek
    EXPECT_EQ(median(cisla), 1);

    cisla = {}; // Prázdný seznam - zde by mohla funkce házet výjimku
    // EXPECT_THROW(median(cisla), std::exception); // Otestuj, zda je vyhozena výjimka
}
