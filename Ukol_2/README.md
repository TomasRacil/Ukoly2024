# Šifrovací algoritmy v C++

Cílem tohoto úkolu je implementovat program v jazyce C++, který bude umět šifrovat a dešifrovat textové soubory pomocí různých šifrovacích algoritmů. Program bude pracovat s textovými soubory a bude obsahovat funkce pro následující algoritmy:

* **Otevření souboru:** Funkce pro otevření textového souboru pro čtení a zápis.
* **Caesarova šifra:** Funkce pro šifrování a dešifrování textu pomocí Caesarovy šifry s volitelným posunem.
* **Vigenerova šifra:** Funkce pro šifrování a dešifrování textu pomocí Vigenerovy šifry s použitím klíčového slova.
* **XOR šifra:** Funkce pro šifrování a dešifrování textu pomocí XOR operace s heslem.

Program by měl být schopen načíst text ze souboru, zašifrovat ho pomocí vybraného algoritmu a uložit zašifrovaný text do nového souboru. Dále by měl být schopen načíst zašifrovaný text a dešifrovat ho zpět do původní podoby.¨

## Popis šifrovacích algoritmů

* **Caesarova šifra:**  Jednoduchá substituční šifra, kde je každé písmeno v otevřeném textu nahrazeno písmenem posunutým o pevný počet pozic v abecedě.
    * Příklad: Posun o 3 pozice: A -> D, B -> E, C -> F atd.
* **Vigenerova šifra:**  Používá klíčové slovo pro posun písmen v textu. Každé písmeno v otevřeném textu je posunuto o jiný počet pozic v abecedě, určený odpovídajícím písmenem v klíčovém slově.
    * Příklad: Klíč "KLIC", text "AHOJ": A je posunuto o K, H o L, O o I, J o C.
* **XOR šifra:**  Provádí bitovou operaci XOR mezi každým znakem textu a odpovídajícím znakem v hesle. Stejné heslo se použije pro šifrování i dešifrování.
    * Příklad: Text "A" (binárně 01000001), heslo "B" (binárně 01000010), zašifrovaný text je 00000011.

## Technické požadavky

* Implementujte program v jazyce C++ s využitím standardní knihovny.
* Pro práci se soubory použijte `std::ifstream` a `std::ofstream`.
* Pro manipulaci s textem využijte `std::string`.
* Implementujte funkce pro každý šifrovací algoritmus s jasně definovanými parametry (vstupní text, klíč/posun, režim šifrování/dešifrování).
* Zajistěte ošetření chybových stavů (např. neexistující soubor, chybné parametry).

## Dokumentace

* Kód by měl být čistý, čitelný a komentovaný.

## Hodnocení

Hodnocení bude brát v úvahu:

* Funkčnost programu a správnost implementace šifrovacích algoritmů.
* Čistotu, čitelnost a komentování kódu.
* Dodržení technických požadavků

## Bonusové body

* Implementace dalších šifrovacích algoritmů (např. Playfairova šifra, Hill šifra)

## Předání úkolu

Úkol odevzdejte ve formě pull requestu zde na GitHubu