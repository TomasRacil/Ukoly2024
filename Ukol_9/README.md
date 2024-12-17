## Zadání úkolu: Správa knihovny

Cílem tohoto úkolu je vytvořit systém pro správu knihovny s využitím objektově orientovaného programování v Pythonu. Zaměříte se na pokročilé koncepty jako setry, getry, dekorátory, statické a class metody.

**Úkoly:**

1. **Třídy:**
    * Vytvořte třídu `Kniha` s atributy: `nazev` (str), `autor` (str), `rok_vydani` (int) a `isbn` (str).
    * Vytvořte třídu `Ctenar` s atributy: `jmeno` (str), `prijmeni` (str), `cislo_prukazky` (int).
    * Vytvořte třídu `Knihovna` s atributy: `nazev` (str) a `knihy` (seznam objektů třídy `Kniha`).

2. **Setry a getry:**
    * Implementujte setry a getry pro atributy `isbn` v třídě `Kniha` a `cislo_prukazky` v třídě `Ctenar`.
    * Setry by měly validovat vstupní data: 
        * `isbn` by mělo mít formát ISBN-13 (13 číslic).
        * `cislo_prukazky` by mělo být kladné celé číslo.
    * V případě neplatných hodnot by setry měly vyvolat ValueError s informativní chybovou zprávou.

3. **Dekorátory:**
    * Vytvořte dekorátor `kniha_existuje`, který bude kontrolovat, zda daná kniha (identifikovaná pomocí ISBN) existuje v knihovně.
    * Použijte tento dekorátor pro metody v třídě `Knihovna`, které pracují s knihami (vypůjčení knihy, odstraneni z knihovny, vraceni knihy).
    * Dekorátor by měl v případě, že kniha neexistuje, vyvolat ValueError s informativní chybovou zprávou.

4. **Statické a class metody:**
    * Implementujte statickou metodu `vygeneruj_cislo_prukazky()` v třídě `Ctenar`, která vygeneruje náhodné číslo průkazky (kladné celé číslo).
    * Implementujte class metodu `z_csv(cls, soubor: str) -> Knihovna` v třídě `Knihovna`, která načte data o knihovně (název knihovny a seznam knih) z CSV souboru.

5. **Další metody:**
    * Implementujte metody pro přidání knihy do knihovny, odebrání knihy z knihovny a vyhledání knihy podle názvu, autora nebo ISBN.
    * Implementujte metody pro registraci čtenáře, zrušení registrace čtenáře a vyhledání čtenáře podle čísla průkazky.
    * Implementujte metody pro vypůjčení a vrácení knihy.


**Hodnocení:**

Hodnocení bude brát v úvahu:

* Funkčnost implementace a správnost metod.
* Správné použití setrů, getrů, dekorátorů, statických a class metod.
* Kvalitu a pokrytí testů.
* Dodržení technických požadavků a principů OOP.
* Čistotu a čitelnost kódu.

**Předání úkolu:**

Úkol odevzdejte na GitHub ve formě pull requestu.
