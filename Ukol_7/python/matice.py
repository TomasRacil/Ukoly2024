

import random

def vytvor_matici(n: int, m: int) -> list[list[int]]:
    return [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]

def reprezentace_matice(matice: list[list[int]]) -> str:
    return '\n'.join(' '.join(str(x) for x in radek) for radek in matice) + '\n' if matice else ""

def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    # Když jsou obě matice prázdné seznamy, vrátíme prázdný seznam
    if matice1 == [] and matice2 == []:
        return []
    # Když jedna z matic je None nebo prázdná, vrátíme None
    if not matice1 or not matice2:
        return None
    # Kontrola rozměrů matic
    if len(matice1) != len(matice2) or len(matice1[0]) != len(matice2[0]):
        print("Chyba: Matice mají různé rozměry, součet není možný.")
        return None
    return [[matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))] for i in range(len(matice1))]

def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    # Když jsou obě matice prázdné seznamy, vrátíme prázdný seznam
    if matice1 == [] and matice2 == []:
        return []
    # Když jedna z matic je None nebo prázdná, vrátíme None
    if not matice1 or not matice2:
        return None
    # Kontrola kompatibility matic pro násobení
    if len(matice1[0]) != len(matice2):
        print("Chyba: Násobení matic není možné, počet sloupců první matice se neshoduje s počtem řádků druhé matice.")
        return None
    return [[sum(matice1[i][k] * matice2[k][j] for k in range(len(matice2))) for j in range(len(matice2[0]))] for i in range(len(matice1))]
def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    if not matice:
        return []
    if matice == [[]]:
        return [[]]
    return [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]

if __name__ == "__main__":
    matice1 = vytvor_matici(3, 2)
    matice2 = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)
    print("Součet matic:")
    print(reprezentace_matice(soucet) if soucet else "Operace není možná.")

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek) if nasobek else "Operace není možná.")

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
