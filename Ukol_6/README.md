## Zadání úkolu: Implementace Hanoiských věží v C++

**Cíl:**

Naučit se aplikovat rekurzi v jazyce C++ na klasický problém Hanoiských věží. Získat zkušenosti s efektivním návrhem algoritmu a jeho vizualizací v konzolovém prostředí.

**Popis:**

Vaším úkolem je napsat program v C++, který řeší problém Hanoiských věží pro zadaný počet disků. Program by měl splňovat následující požadavky:

*   Umožnit uživateli zadat počet disků.
*   Vypsat v konzoli jednotlivé kroky potřebné k přesunutí všech disků z počátečního kolíku na cílový kolík, v souladu s pravidly Hanoiských věží.
*   Po každém kroku zobrazit aktuální stav věží v konzoli.

**Pravidla Hanoiských věží:**

*   Máme k dispozici tři kolíky (označené A, B, C).
*   Na počátečním kolíku (A) je umístěno n disků různých velikostí, seřazených od největšího dole po nejmenší nahoře.
*   Cílem je přesunout všechny disky na cílový kolík (C).
*   V každém kroku lze přesunout pouze jeden disk.
*   Větší disk nesmí být nikdy umístěn na menší disk.

**Pokyny k implementaci:**

*   Pro řešení problému použijte rekurzivní funkci `hanoi`.
*   Vypisujte kroky v následujícím formátu: "Přesuň disk  `číslo disku`  z kolíku  `označení kolíku`  na kolík  `označení kolíku`."
*   Pro vizualizaci věží v konzoli využijte funkci `zobrazVeze`.
*   Snažte se o efektivní a srozumitelný kód s komentáři.

**Příklad vizualizace:**

```
    |              |             |
   ===             |             |
  =====            |             |
 =======           |             |
=========          |             |
```

**Struktura kódu:**

K implementaci vašeho řešení použijte následující strukturu:

```c++
#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Člen pro uložení stavu věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>> &veze, Tah tah) {
    // Doplňte implementaci
}

// Funkce pro řešení Hanoiských věží (bez výpisu)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>> &veze, vector<Tah> &tahy) {
    
}

void zobrazVeze(vector<vector<int>> &veze) {
    // Doplňte implementaci
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (Tah tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
```

**Doplňující informace:**

*   Využijte strukturu `Tah` pro uložení informací o každém provedeném tahu.
*   Funkce `provedTah` slouží k aktualizaci stavu věží po provedení tahu.
*   Funkce `zobrazVeze` by měla zobrazit aktuální stav věží v konzoli.
*   Nezapomeňte na ošetření chybových stavů (např. neplatný počet disků).

**Hodnocení:**

*   **SPLNĚNÍ AUTOMATICKÝCH TESTŮ**
*   Správná implementace algoritmu pro řešení Hanoiských věží.
*   Efektivita a srozumitelnost kódu.
*   Kvalita vizualizace v konzoli.
*   Dodržování pokynů a formátování kódu.

