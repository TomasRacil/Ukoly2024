## Maticové operace v Pythonu - Objektově orientované programování (aktualizované)

V tomto úkolu navážete na předchozí implementaci maticových operací a přepíšete ji s využitím objektově orientovaného programování (OOP) s důrazem na přetížení operátorů a typové hinty.

### Úkoly

1. **Vytvořte třídu `Matice` (doplnění šablony):**

    * **Konstruktor:** Implementujte konstruktor `__init__(self, n: int, m: int, data=None)`, který inicializuje matici o rozměrech `n` x `m`. Argument `data` bude volitelný a umožní inicializovat matici s předem definovanými hodnotami. **Pokud `data` není zadáno, matice se naplní náhodnými celými čísly v rozsahu od 0 do 9.**
    * **Reprezentace:** Doplňte implementaci metody `__str__(self) -> str`, která vrátí stringovou reprezentaci matice, kde každý řádek matice bude v samostatném řádku a prvky v řádku budou odděleny mezerami.
    * **Sčítání:** Doplňte implementaci metody `__add__(self, other: Matice) -> Matice`, která sečte aktuální matici s maticí `other`. Metoda by měla zkontrolovat, zda je součet proveditelný.
    * **Násobení:** Doplňte implementaci metody `__mul__(self, other: Union[Matice, int]) -> Matice`, která vynásobí aktuální matici s maticí `other` nebo s celým číslem (skalárem). Metoda by měla zkontrolovat, zda je násobení proveditelné a v případě násobení skalárem vrátit novou matici s vynásobenými prvky.
    * **Transpozice:** Doplňte implementaci metody `transpozice(self) -> Matice`, která vrátí transponovanou matici.

2. **Otestujte metody třídy `Matice`:**

    * Využijte kód v bloku `if __name__ == "__main__":` pro vytvoření instancí třídy `Matice` a otestování všech implementovaných metod, včetně přetížených operátorů `+` a `*` pro sčítání a násobení.


### Technické požadavky

* Implementujte řešení v jazyce Python.
* Kód by měl být čistý, čitelný a komentovaný.
* Pro generování náhodných čísel můžete použít modul `random`.
* Použijte typové hinty pro všechny metody a proměnné.

### Hodnocení

Hodnocení bude brát v úvahu:

* Funkčnost implementace a správnost maticových operací.
* Dodržení technických požadavků a principů OOP.
* Čistotu a čitelnost kódu.

### Předání úkolu

Úkol odevzdejte na GitHub ve formě pull requestu.