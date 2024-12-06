from random import randrange as rr

def vytvor_matici(pocet_radku: int, pocet_sloupcu: int) -> list[list[int]]:
    if pocet_radku == 0 or pocet_sloupcu == 0:
        return [[] for _ in range(pocet_radku)] if pocet_radku != 0 else []
    return [[rr(10) for _ in range(pocet_sloupcu)] for _ in range(pocet_radku)]

def reprezentace_matice(matice: list[list[int]]) -> str:
    if not matice:
        return ""
    return "\n".join(" ".join(map(str, radek)) for radek in matice) + "\n"  # Opraveno přidání nového řádku

def soucet_matic(matice_1: list[list[int]], matice_2: list[list[int]]) -> list[list[int]]:
    if not matice_1 or not matice_2 or len(matice_1) != len(matice_2) or len(matice_1[0]) != len(matice_2[0]):
        return None  # Opraveno: vracíme None, ne prázdný seznam
    return [[matice_1[r][s] + matice_2[r][s] for s in range(len(matice_1[0]))] for r in range(len(matice_1))]

def nasobeni_matic(matice_1: list[list[int]], matice_2: list[list[int]]) -> list[list[int]]:
    if not matice_1 or not matice_2 or len(matice_1[0]) != len(matice_2):
        return None  # Opraveno: vracíme None, ne prázdný seznam
    return [
        [
            sum(matice_1[i][k] * matice_2[k][j] for k in range(len(matice_2)))  # len slouží ke zjištění délky...
            for j in range(len(matice_2[0]))
        ]
        for i in range(len(matice_1))
    ]

def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    if not matice or not matice[0]:  # Opraveno: kontrola na prázdný seznam nebo prázdný vnitřní seznam
        return [[]]  # Opraveno pro správný výstup prázdné matice
    return [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]

if __name__ == "__main__":
    pocet_radku = int(input("Pocet radku: "))
    pocet_sloupcu = int(input("Pocet sloupcu: "))

    matice_1 = vytvor_matici(pocet_radku, pocet_sloupcu)
    matice_2 = vytvor_matici(pocet_radku, pocet_sloupcu)

    print("Matice 1:")
    print(reprezentace_matice(matice_1))

    print("Matice 2:")
    print(reprezentace_matice(matice_2))

    soucet = soucet_matic(matice_1, matice_2)
    if soucet:
        print("Soucet matic:")
        print(reprezentace_matice(soucet))
    else:
        print("Součet matic není možný (neshodné rozměry).")

    nasobek = nasobeni_matic(matice_1, matice_2)
    if nasobek:
        print("Nasobeni matic:")
        print(reprezentace_matice(nasobek))
    else:
        print("Násobení matic není možné (neshodné rozměry).")

    print("Transponovana matice 1:")
    print(reprezentace_matice(transpozice_matice(matice_1)))
