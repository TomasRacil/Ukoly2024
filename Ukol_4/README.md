## Navigace lodi (Advent of Code)

Cílem tohoto úkolu je naprogramovat v jazyce C++ navigaci lodi, která se pohybuje po moři podle navigačních instrukcí.

[Příklad vychází z tohoto zadání Advent of Code.](https://adventofcode.com/2021/day/12)

### Popis problému

Loď se pohybuje po 2D mřížce a její pozice je určena souřadnicemi x a y. Loď přijímá navigační instrukce ve formátu "akce hodnota", například "F10" (pohyb vpřed o 10 jednotek), "N3" (pohyb na sever o 3 jednotky), "R90" (otočení doprava o 90 stupňů). Loď začíná na pozici 0,0 a směřuje na východ.

**Seznam akcí:**

* **N, S, E, W:** Pohyb na sever, jih, východ, západ o daný počet jednotek.
* **L, R:** Otočení doleva, doprava o daný počet stupňů.
* **F:** Pohyb vpřed o daný počet jednotek ve směru, kterým loď aktuálně směřuje.

### Úkoly

**Část 1:**

1. Načtěte navigační instrukce ze vstupního souboru.
2. Implementujte funkci `navigate`, která provede loď danými instrukcemi.
3. Spočítejte Manhattan vzdálenost (součet absolutních hodnot x a y souřadnic) lodi od jejího počátečního bodu po provedení všech instrukcí.

**Část 2:**

1. Upravte funkci `navigate` tak, aby zohledňovala waypoint. Waypoint je bod v prostoru, který se pohybuje relativně k lodi.
2. Akce N, S, E a W nyní pohybují waypointem, nikoli lodí.
3. Akce L a R otáčejí waypoint kolem lodi.
4. Akce F pohybuje lodí směrem k waypointu o daný počet krát.
5. Spočítejte Manhattan vzdálenost lodi od jejího počátečního bodu po provedení všech instrukcí s waypointem.

### Technické požadavky

* Implementujte řešení v jazyce C++.
* Kód by měl být čistý, čitelný a komentovaný.

### Hodnocení

Hodnocení bude brát v úvahu:

* Funkčnost implementace a správnost výpočtu Manhattan vzdálenosti.
* Dodržení technických požadavků.
* Čistotu a čitelnost kódu.

### Předání úkolu

Úkol odevzdejte ve formě pull requestu zde na GitHubu.
