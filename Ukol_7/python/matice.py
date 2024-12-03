import random

def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    matice: list[list[int]] = []
    for i in range(n):
        radek: list[int] = []  # vytvoreni prazdneho radku
        for j in range(m):
            radek.append(random.randint(0, 9))  # do radku pridava nahodne cislo 0 az 9
        matice.append(radek)
    return matice


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""
    if not matice:
        return ""
    reprezentace = ""
    for radek in matice:
        reprezentace += " ".join(map(str, radek)) + "\n"
    return reprezentace


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    if len(matice1) != len(matice2) or any(len(row1) != len(row2) for row1, row2 in zip(matice1, matice2)):
        print("Nelze sečíst z důvodu rozdilných rozměrů matic")
        return None

    vysledek: list[list[int]] = []
    for i in range(len(matice1)):
        radek: list[int] = []
        for j in range(len(matice1[i])):
            radek.append(matice1[i][j] + matice2[i][j])
        vysledek.append(radek)
    return vysledek


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    if not matice1 or not matice2 or len(matice1[0]) != len(matice2):
        print("Matice nelze vynásobit")
        return None

    vysledek = [[0 for _ in range(len(matice2[0]))] for _ in range(len(matice1))]
    for i in range(len(matice1)):
        for j in range(len(matice2[0])):
            for k in range(len(matice1[0])):
                vysledek[i][j] += matice1[i][k] * matice2[k][j]
    return vysledek


def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice."""
    if not matice:
        print("Matice je prázdná")
        return []
    if all(len(radek) == 0 for radek in matice):
        return [[]]
    transponovana = [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]
    return transponovana


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)
    print("Součet matic:")
    print(reprezentace_matice(soucet) if soucet else "Nelze sečíst.")

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek) if nasobek else "Nelze násobit.")

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
