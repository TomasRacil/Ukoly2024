import random


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    return [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""
    return "\n".join(" ".join(map(str, row)) for row in matice) + ("\n" if matice else "")


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    if len(matice1) != len(matice2) or any(len(row1) != len(row2) for row1, row2 in zip(matice1, matice2)):
        return None
    return [[el1 + el2 for el1, el2 in zip(row1, row2)] for row1, row2 in zip(matice1, matice2)]


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    if not matice1 or not matice2 or len(matice1[0]) != len(matice2):
        return None
    return [[
        sum(matice1[i][k] * matice2[k][j] for k in range(len(matice2)))
        for j in range(len(matice2[0]))
    ] for i in range(len(matice1))]


def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice."""
    return [list(row) for row in zip(*matice)]


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    print(reprezentace_matice(soucet) if soucet else "Operace se nezdařila.")

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek) if nasobek else "Operace se nezdařila.")

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
