import random 


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    if n == 0:
        return []
    matice: list[list[int]] = [[random.randint(0,9) for _ in range(m)] for _ in range(n)]
    return matice


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""
    if not matice:
        return ""
    return '\n'.join(' '.join(map(str, radek)) for radek in matice) + '\n'


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    if len(matice1) != len(matice2) or any(len(radek1) != len(radek2) for radek1, radek2 in zip(matice1, matice2)):
        return None
    matice: list[list[int]] = [[a + b for a, b in zip(radek1, radek2)]for radek1, radek2 in zip(matice1, matice2)] 
    return matice
    


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    if not matice1 or not matice2:
        return []
    if not matice1 or not matice2 or len(matice1[0]) != len(matice2):
        return None
    
    # Transponování druhé matice pro efektivnější práci s ní
    matice2_transponovana = list(zip(*matice2))
    
    # Vytvoření výsledné matice součinu
    matice: list[list[int]] = [[sum(a * b for a, b in zip(radek1, radek2))for radek2 in matice2_transponovana]for radek1 in matice1]   
    return matice

    


def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice."""
    if not matice or not matice[0]:
        return [[]] if matice else []
    else:
        matice: list[list[int]] = [list(radek) for radek in zip(*matice)]
        return matice


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    if soucet is not None:
        print(reprezentace_matice(soucet))

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    if nasobek is not None:
        print(reprezentace_matice(nasobek))

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
