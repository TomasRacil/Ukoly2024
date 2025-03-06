import random

def vytvor_matici(n: int, m: int) -> list[list[int]]:
    if n <= 0:
        return []
    return [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]

def reprezentace_matice(matice: list[list[int]]) -> str:
    s = ""
    for radek in matice:
        s += " ".join(str(x) for x in radek) + "\n"
    return s

def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    if matice1 == [] and matice2 == []:
        return []

    if matice1 == [] or matice2 == []:
        print("chyba - matice maji ruzne rozmery")
        return None
    if len(matice1) != len(matice2):
        print("chyba - matice nemaji stejny pocet radku")
        return None
    vysledek = []
    for row1, row2 in zip(matice1, matice2):
        if len(row1) != len(row2):
            print("chyba - matice nemaji stejny pocet sloupcu")
            return None
        vysledek.append([a + b for a, b in zip(row1, row2)])
    return vysledek

def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    if matice1 == [] and matice2 == []:
        return []
    if matice1 == [] or matice2 == []:
        print("chyba - nejde nasobit matici s prazdnou matici")
        return None
    num_rows1 = len(matice1)
    num_cols1 = len(matice1[0])
    num_rows2 = len(matice2)
    num_cols2 = len(matice2[0])
    if num_cols1 != num_rows2:
        print("chyba - poocet sloupcu prvni matice se nerova poctu radku druhe")
        return None
    vysledek = [[0 for _ in range(num_cols2)] for _ in range(num_rows1)]
    for i in range(num_rows1):
        for j in range(num_cols2):
            for k in range(num_cols1):
                vysledek[i][j] += matice1[i][k] * matice2[k][j]
    return vysledek

def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    if matice == []:
        return []
    if len(matice) > 0 and len(matice[0]) == 0:
        return [[]]
    return [list(radek) for radek in zip(*matice)]


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("matice 1")
    print(reprezentace_matice(matice1))
    print("matice 2")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)
    print("součet matic")
    print(reprezentace_matice(soucet))

    nasobek = nasobeni_matic(matice1, matice2)
    print("nasobeni matic")
    print(reprezentace_matice(nasobek))

    transponovana = transpozice_matice(matice1)
    print("transponovana matice")
    print(reprezentace_matice(transponovana))
