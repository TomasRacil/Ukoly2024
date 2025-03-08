## Maticové operace v Pythonu

Cílem tohoto úkolu je naprogramovat v jazyce Python program, který bude provádět základní maticové operace. Matice budou reprezentovány jako seznam seznamů (list of lists) v Pythonu. 

### Úkoly

**Část 1: Základní funkce**

1. Implementujte funkci `vytvor_matici(n, m)`, která vytvoří matici o rozměrech `n` x `m` náhodně naplněnou celými čísly v rozsahu od 0 do 9.
2. Implementujte funkci `reprezentace_matice(matice)`, která vrátí stringovou reprezentaci matice, kde každý řádek matice bude v samostatném řádku a prvky v řádku budou odděleny mezerami.
3. Implementujte funkci `soucet_matic(matice1, matice2)`, která provede součet dvou matic. Funkce by měla zkontrolovat, zda je součet proveditelný (tj. zda mají matice stejné rozměry). Pokud součet není proveditelný, funkce by měla vypsat chybové hlášení a vrátit `None`.
4. Implementujte funkci `nasobeni_matic(matice1, matice2)`, která provede násobení dvou matic. Funkce by měla zkontrolovat, zda je násobení proveditelné (tj. zda počet sloupců první matice je roven počtu řádků druhé matice). Pokud násobení není proveditelné, funkce by měla vypsat chybové hlášení a vrátit `None`.
5. Implementujte funkci `transpozice_matice(matice)`, která provede transpozici matice (záměnu řádků a sloupců).

### Technické požadavky

* Implementujte řešení v jazyce Python.
* Kód by měl být čistý, čitelný a komentovaný.
* Pro generování náhodných čísel můžete použít modul `random`.

### Hodnocení

Hodnocení bude brát v úvahu:

* Funkčnost implementace a správnost maticových operací.
* Dodržení technických požadavků.
* Čistotu a čitelnost kódu.
* Efektivitu implementace (pro bonusové úkoly).

### Předání úkolu

Úkol odevzdejte na GitHub ve formě pull requestu.
