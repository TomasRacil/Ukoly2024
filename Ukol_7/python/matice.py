import random

def vytvor_matici(n, m):
    return [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]

def reprezentace_matice(matice):
    
    return '\n'.join(' '.join(map(str, radek)) for radek in matice)

def soucet_matic(matice1, matice2):
    
    
    if len(matice1) != len(matice2) or len(matice1[0]) != len(matice2[0]):
        print("Chyba: Matice nemají stejné rozměry.")
        return None
    return [[matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))] for i in range(len(matice1))]

def nasobeni_matic(matice1, matice2):
    
    if len(matice1[0]) != len(matice2):
        print("Chyba: Počet sloupcu první matice není roven počtu řádků druhé matice.")
        return None
    vysledek = [[0 for _ in range(len(matice2[0]))] for _ in range(len(matice1))]
    for i in range(len(matice1)):
        for j in range(len(matice2[0])):
            for k in range(len(matice2)):
                vysledek[i][j] += matice1[i][k] * matice2[k][j]
    return vysledek

def transpozice_matice(matice):
    """
    Provede transpozici matice (záměnu řádků a sloupců).
    """
    return [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]


if __name__ == "__main__":
    n, m = 3, 3
    matice1 = vytvor_matici(n, m)
    matice2 = vytvor_matici(n, m)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("\nMatice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice2)
    if soucet:
        print("\nSoučet matic:")
        print(reprezentace_matice(soucet))

    matice3 = vytvor_matici(m, n)
    nasobeni = nasobeni_matic(matice1, matice3)
    if nasobeni:
        print("\nNásobení matic:")
        print(reprezentace_matice(nasobeni))

    transpozice = transpozice_matice(matice1)
    print("\nTranspozice matice 1:")
    print(reprezentace_matice(transpozice))
