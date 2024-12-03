import random


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    return [[random.randint(0, 9) for _ in range(m)] for _ in range(n)] # Vytvoří matici n × m s náhodnými čísly 0–9.


def reprezentace_matice(matice: list[list[int]]) -> str:
    return "\n".join(" ".join(map(str, radek)) for radek in matice) # Převede matici na formátovaný řetězec s čísly oddělenými mezerami.


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    if len(matice1) != len(matice2) or len(matice1[0]) != len(matice2[0]): # Kontroluje, zda mají matice stejné rozměry.
        raise ValueError("Matice nemají stejné rozměry!") # Vyvolá chybu, pokud rozměry nesouhlasí.
    return [[matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))] for i in range(len(matice1))]  # Sečte odpovídající prvky matic.


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    if len(matice1[0]) != len(matice2): # Kontroluje, zda je počet sloupců první matice roven počtu řádků druhé matice.
        raise ValueError("Počet sloupců matice 1 se nerovná počtu řádků matice 2!") # Vyvolá chybu, pokud násobení není možné.
    return [[sum(matice1[i][k] * matice2[k][j] for k in range(len(matice2))) for j in range(len(matice2[0]))] for i in range(len(matice1))]  # Pro každý prvek výsledné matice spočítá skalární součin odpovídajícího řádku a sloupce.


def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    return [list(radek) for radek in zip(*matice)]  # Provede transpozici (převede řádky na sloupce a naopak).


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2) # Vytvoří matici o rozměrech 3 × 2 s náhodnými čísly.
    matice2: list[list[int]] = vytvor_matici(2, 4)  # Vytvoří matici o rozměrech 2 × 4 s náhodnými čísly.

    print("Matice 1:")
    print(reprezentace_matice(matice1)) # Vypíše reprezentaci matice 1 jako text.
    print("Matice 2:")
    print(reprezentace_matice(matice2)) # Vypíše reprezentaci matice 2 jako text.

    soucet = soucet_matic(matice1, matice1)  # Sečteme matici 1 samu se sebou
    print("Součet matic:")
    print(reprezentace_matice(soucet)) # Vypíše výslednou matici po součtu.

    nasobek = nasobeni_matic(matice1, matice2) # Vynásobí matici 1 a matici 2.
    print("Násobení matic:")
    print(reprezentace_matice(nasobek)) # Vypíše výslednou matici po násobení.

    transponovana = transpozice_matice(matice1) # Provede transpozici matice 1.
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana)) # Vypíše transponovanou matici.
