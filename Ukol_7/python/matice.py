import random

MIN_VALUE = 0
MAX_VALUE = 9

def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    matice: list[list[int]] = [[random.randint(MIN_VALUE, MAX_VALUE) for a in range(m)] for a in range(n)]
    return matice


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""
    if matice:
        str_mat = ""
        for radek in matice:
            str_mat += " ".join(map(str, radek)) + "\n"
        return str_mat
    else: return ""


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    if not matice1 and not matice2: return []
    matice: list[list[int]] = []
    if len(matice1) != len(matice2) or any(len(radek1) != len(radek2) for radek1, radek2 in zip(matice1, matice2)):
        return None
    
    rows = len(matice1)
    cols = len(matice1[0])
    matice = [[0 for i in range(cols)] for i in range(rows)]
    for row in range(rows):
        for col in range(cols):
            matice[row][col] = matice1[row][col] + matice2[row][col]
    return matice

def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    # Zkontrolovat, zda matice nejsou prazdne
    if not matice1 and not matice2:
        return []
    if not matice1 or not matice2:
        return None
    if len(matice1[0]) != len(matice2):
        return None
    pocet_radku = len(matice1)
    pocet_sloupcu = len(matice2[0])
    spolecna_dim = len(matice2)
    # Inicializace vysledne matice nulami
    matice = [[0 for _ in range(pocet_sloupcu)] for _ in range(pocet_radku)]

    # Vypocet jednotlivych prvku vysledne matice
    for i in range(pocet_radku):
        for j in range(pocet_sloupcu):
            matice[i][j] = sum(matice1[i][k] * matice2[k][j] for k in range(spolecna_dim))
    return matice


def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice."""
    if not matice: return []
    if not matice[0]: return [[]]
    matice: list[list[int]] = [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]
    return matice


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(2, 2)
    matice2: list[list[int]] = vytvor_matici(2, 2)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)
    print("Součet matic:")
    print(reprezentace_matice(soucet))

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek))

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
