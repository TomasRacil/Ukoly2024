import random


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    matice: list[list[int]] = [] # Vytvoření prázdné matice
    for i in range(n):  # Procházení řádků
        radek: list[int] = []  # Vytvoření prázdného řádku
        for j in range(m):  # Procházení sloupců
            radek.append(random.randint(0, 9))  # Přidání náhodného čísla do řádku
        matice.append(radek)  # Přidání řádku do matice

    return matice


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""

    if matice:
        reprezentace = "" # Inicializace reprezentace
        for radek in matice: # Procházení řádků
            reprezentace += " ".join(map(str, radek)) + "\n" # Přidání řádku do reprezentace
        return reprezentace
    else:

        return ""


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    if not matice1 and not matice2:   # Pokud jsou obě matice prázdné
        print("Obě matice jsou prázdné")
        return []

    if len(matice1) == len(matice2) and all(len(row) == len(matice2[i]) for i, row in enumerate(matice1)):
        matice: list[list[int]] = [] # Vytvoření prázdné matice pro výsledek
        for i in range(len(matice1)): # Procházení řádků
            radek: list[int] = [] # Vytvoření prázdného řádku
            for j in range(len(matice1[i])): # Procházení sloupců
                radek.append(matice1[i][j] + matice2[i][j]) # Sečtení prvků a přidání do řádku
            matice.append(radek) # Přidání řádku do matice
        return matice
    else:
        print("Matice nemají stejné rozměry")
        return None


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    # Zkontrolovat, zda matice nejsou prázdné
    if not matice1 and not matice2:
        return []
    if not matice1 or not matice2:
        return None
    # Rozměry matic
    m1_rows, m1_cols = len(matice1), len(matice1[0])
    m2_rows, m2_cols = len(matice2), len(matice2[0])

    # Zkontrolovat kompatibilitu pro násobení
    if m1_cols != m2_rows:
        print("Matice nejsou kompatibilní pro násobení")
        return None

    # Inicializovat výslednou matici nulami
    # Počet řádků je roven počtu řádků první matice a počet sloupců je roven počtu sloupců druhé matice
    result = [[0 for _ in range(m2_cols)] for _ in range(m1_rows)] # Vytvoření matice s nulami po zmeně rozměrů

    # Výpočet výsledné matice
    for i in range(m1_rows):  # Procházení řádků první matice
        for j in range(m2_cols):   # Procházení sloupců druhé matice
            for k in range(m1_cols):  # Procházení sloupců první matice
                result[i][j] += matice1[i][k] * matice2[k][j]  # Násobení prvků a přičtení do výsledné matice

    return result


def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Transponuje danou matici."""
    if not matice:
        print("Matice je prázdná")
        return []
    if not matice[0]:
        print("Matice nemá žádné sloupce")
        return [[]]

    # i = řádek, j = sloupec
    transponovana = [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]
    return transponovana


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    print(reprezentace_matice(soucet))

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek))

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
