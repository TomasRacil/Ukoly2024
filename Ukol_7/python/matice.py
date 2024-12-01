import random


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    matice: list[list[int]] = [] 
    for i in range(n):  # Prochazeni radku
        radek: list[int] = []  
        for j in range(m):  # Prochazeni sloupcu
            radek.append(random.randint(0, 9))  # Pridani nahodneho cisla do radku
        matice.append(radek)  # Pridani radku do matice

    return matice


def reprezentace_matice(matice: list[list[int]]) -> str:

    if matice:
        reprezentace = "" # Inicializace reprezentace
        for radek in matice: # Prochazeni radku
            reprezentace += " ".join(map(str, radek)) + "\n" # Pridani radku do reprezentace
        return reprezentace
    else:

        return ""


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    if not matice1 and not matice2:   # Pokud jsou obe matice prazdne
        print("Obe matice nejsou zadany")
        return []

    if len(matice1) == len(matice2) and all(len(row) == len(matice2[i]) for i, row in enumerate(matice1)):
        matice: list[list[int]] = [] # Vytvoreni prazdne matice pro vysledek
        for i in range(len(matice1)): 
            radek: list[int] = [] 
            for j in range(len(matice1[i])): 
                radek.append(matice1[i][j] + matice2[i][j]) # Secteni prvku a pridani do radku
            matice.append(radek) 
        return matice
    else:
        print("Matice nemaji stejne rozmery")
        return None


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    # Zkontrolovat, zda matice nejsou prazdne
    if not matice1 or not matice2:  # Pokud je alespon jedna matice prazdna
        print("chybny vstup")
        return None

    # Rozmery matic
    m1_rows, m1_cols = len(matice1), len(matice1[0])
    m2_rows, m2_cols = len(matice2), len(matice2[0])

    # Zkontrolovat kompatibilitu pro nasobeni
    if m1_cols != m2_rows:
        print("Nemuzeme nasobit")
        return None

    # Inicializovat vyslednou matici nulami
    result = [[0 for _ in range(m2_cols)] for _ in range(m1_rows)] # Vytvoreni matice s nulami po zmene rozmeru

    # vypocet vysledne matice
    for i in range(m1_rows):  # Prochazení radku prvni matice
        for j in range(m2_cols):   # Prochazeni sloupcu druhe matice
            for k in range(m1_cols):  # Prochazeni sloupcu prvni matice
                result[i][j] += matice1[i][k] * matice2[k][j]  # Nasobeni prvku a pricteni do vysledne matice

    return result


def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    if not matice:
        print("Matice je prazdna")
        return []
    if not matice[0]:
        print("Matice nema sloupce")
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

    soucet = soucet_matic(matice1, matice1)  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    print(reprezentace_matice(soucet))

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek))

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
