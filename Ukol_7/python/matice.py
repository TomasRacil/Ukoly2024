# matice.py
def vytvor_matici(radky: int, sloupce: int) -> list[list[int]]:
    if radky == 0 or sloupce == 0:
        return []  # Prázdná matice, pokud je počet řádků nebo sloupců 0
    return [[random.randint(0, 9) for _ in range(sloupce)] for _ in range(radky)]

def reprezentace_matice(matice: list[list[int]]) -> str:
    if not matice:
        return ""  # Pokud je matice prázdná, vrátí prázdný řetězec
    return "\n".join(" ".join(map(str, radek)) for radek in matice) + "\n"

def soucet_matic(matice_1: list[list[int]], matice_2: list[list[int]]) -> list[list[int]]:
    if not matice_1 or not matice_2 or len(matice_1) != len(matice_2) or len(matice_1[0]) != len(matice_2[0]):
        return []  # Vrátí prázdný seznam pro nekompatibilní nebo prázdné matice
    return [[matice_1[r][s] + matice_2[r][s] for s in range(len(matice_1[0]))] for r in range(len(matice_1))]

def nasobeni_matic(matice_1: list[list[int]], matice_2: list[list[int]]) -> list[list[int]]:
    if not matice_1 or not matice_2 or len(matice_1[0]) != len(matice_2):
        return []  # Vrátí prázdný seznam pro nekompatibilní nebo prázdné matice
    return [
        [
            sum(matice_1[i][k] * matice_2[k][j] for k in range(len(matice_2)))  # len slouží ke zjištění délky...
            for j in range(len(matice_2[0]))
        ]
        for i in range(len(matice_1))
    ]

def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    if not matice:  # Opraveno: vracíme prázdný seznam pro prázdnou matici
        return []
    return [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]
