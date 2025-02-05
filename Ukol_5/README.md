## Zadání úkolu: Refaktoring simulace ekosystému v C++

**Cíl:**

Prokázat znalost rozdělení kódu do hlavičkových a zdrojových souborů v jazyce C++. Zaměřte se na **správnou organizaci kódu, minimalizaci závislostí a použití include guardů**.

**Popis:**

Váš úkol je refaktorovat existující kód simulace ekosystému, který jste vytvářeli v hodině. Kód je potřeba rozdělit do hlavičkových a zdrojových souborů podle vámi vytcvořených tříd. Například:

* **organismus.h / organismus.cpp:**  Abstraktní třída `Organismus` a její metody.
* **zvire.h / zvire.cpp:** Třída `Zvire` dědící z `Organismus` a implementující společné metody pro býložravce a masožravce.
* **rostlina.h / rostlina.cpp:** Třída `Rostlina` dědící z `Organismus`.
* **bylozravec.h / bylozravec.cpp:** Třída `Bylozravec` dědící z `Zvire`.
* **masozravec.h / masozravec.cpp:** Třída `Masozravec` dědící z `Zvire`.
* **prostredi.h / prostredi.cpp:** Třída `Prostredi` spravující ekosystém a organismy.
* **source.cpp:** Hlavní program pro spuštění simulace.

**Pokyny:**

1. **Deklarace v hlavičkových souborech (.h):** Umístěte deklarace tříd do hlavičkových souborů.
2. **Definice ve zdrojových souborech (.cpp):**  Implementujte metody tříd ve zdrojových souborech.
3. **Include guardy:** Použijte include guardy v každém hlavičkovém souboru, abyste zabránili vícenásobnému vložení.
4. **Minimalizace závislostí:** Snažte se minimalizovat závislosti mezi soubory. Vkládejte pouze ty hlavičkové soubory, které jsou nezbytně nutné.
5. **Forward deklarace:**  Použijte forward deklarace tam, kde je to možné, abyste snížili závislosti mezi soubory.

**Příklad include guardu:**

```c++
#ifndef ORGANISMUS_H
#define ORGANISMUS_H

// Deklarace třídy Organismus

#endif
```

**Hodnocení:**

* Správné rozdělení kódu do hlavičkových a zdrojových souborů.
* Použití include guardů ve všech hlavičkových souborech.
* Minimalizace závislostí mezi soubory.
* Čitelnost a organizace kódu.


**Tipy:**

* Začněte s rozdělením kódu pro nejjednodušší třídy.
* Postupně přidávejte další třídy a řešte závislosti mezi nimi.
* Použijte forward deklarace pro třídy, které jsou pouze referencovány (nepoužívají se jejich metody).
* Pravidelně kompilujte kód a opravujte případné chyby.
