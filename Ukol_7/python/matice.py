import random
from typing import List, Optional

def vytvor_matici(n: int, m: int) -> List[List[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    return [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]

def reprezentace_matice(matice: List[List[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""
    return "\n".join(" ".join(map(str, row)) for row in matice) + ("\n" if matice else "")

def soucet_matic(matice1: List[List[int]], matice2: List[List[int]]) -> Optional[List[List[int]]]:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    if len(matice1) != len(matice2) or any(len(row1) != len(row2) for row1, row2 in zip(matice1, matice2)):
        return None

    return [[elem1 + elem2 for elem1, elem2 in zip(row1, row2)] for row1, row2 in zip(matice1, matice2)]

def nasobeni_matic(matice1: List[List[int]], matice2: List[List[int]]) -> Optional[List[List[int]]]:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    if not matice1 or not matice2:  
        return [] if matice1 == matice2 == [] else None
    if len(matice1[0]) != len(matice2): 
        return None

    return [[
        sum(a * b for a, b in zip(row, col))
        for col in zip(*matice2)
    ] for row in matice1]

def transpozice_matice(matice: List[List[int]]) -> List[List[int]]:
    """Provede transpozici matice."""
    if not matice:
        return []
    if matice == [[]]:
        return [[]]
    return [list(row) for row in zip(*matice)]

if __name__ == "__main__":
    matice1: List[List[int]] = vytvor_matici(3, 2)
    matice2: List[List[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))

    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)
    print("Součet matic:")
    print(reprezentace_matice(soucet) if soucet is not None else "Nelze sečíst matice.")

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek) if nasobek is not None else "Nelze násobit matice.")

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
