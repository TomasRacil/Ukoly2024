import random


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    matice = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]
    return matice


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice. Pokud je matice prázdná, vrátí prázdný řetězec."""
    if not matice:
        return ""
    return "\n".join(" ".join(map(str, radek)) for radek in matice)


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Sečte dvě matice, pokud mají stejné rozměry. Pokud jsou matice prázdné, vrátí prázdnou matici."""
    if not matice1 and not matice2:
        return []
    if len(matice1) != len(matice2) or len(matice1[0]) != len(matice2[0]):
        return None
    return [
        [matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))]
        for i in range(len(matice1))
    ]




def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Vynásobí dvě matice, pokud je násobení proveditelné. Jinak vrátí None."""
    if len(matice1[0]) != len(matice2):
        return None
    return [
        [
            sum(matice1[i][k] * matice2[k][j] for k in range(len(matice2)))
            for j in range(len(matice2[0]))
        ]
        for i in range(len(matice1))
    ]



def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice. Pokud je matice prázdná nebo obsahuje prázdné řádky, vrátí prázdnou matici."""
    if not matice or not matice[0]:
        return []
    return [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    try:
        soucet = soucet_matic(matice1, matice1)  # Sečteme matici1 samu se sebou
        print("Součet matic:")
        print(reprezentace_matice(soucet))
    except ValueError as e:
        print(f"Chyba při sčítání: {e}")

    try:
        nasobek = nasobeni_matic(matice1, matice2)
        print("Násobení matic:")
        print(reprezentace_matice(nasobek))
    except ValueError as e:
        print(f"Chyba při násobení: {e}")

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
