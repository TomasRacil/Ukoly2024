import random


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    matice: list[list[int]] = []
    for i in range(0,n):
        radek:list[int] = []
        for j in range(0,m):
            radek.append(random.randint(0,9))
        matice.append(radek)
    return matice


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""
    s:str  = ""
    for radek in matice:
        for cislo in radek:
            s += str(cislo) + " "
        s+= "\n"
    return s


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    matice: list[list[int]] = []
    if len(matice1) == len(matice2) and len(matice1[0]) == len(matice2[0]):
        for i in range (0,len(matice1)):
            radek:list[int] = []
            for j in range(0,len(matice1[0])):
                soucet = matice1[i][j] + matice2[i][j]
                radek.append(soucet)
            matice.append(radek)
        return matice
    else:
        print("tyto matice nejde scitat")
        return None
    
        
                
    


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    matice: list[list[int]] = []
    if len(matice1[0]) == len(matice2):
        for i in range(0,len(matice1)):
            radek:list = []
            for j in range(0,len(matice2[0])):
                soucin = 0
                for k in range (0,len(matice2)):
                    soucin += matice1[i][k] * matice2[k][j]
                radek.append(soucin)
            matice.append(radek)
        return matice
    else:
        print("tyto matice nejde nasobit")
        return None
    


def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice."""
    nmatice: list[list[int]] = []
    for i in range(0,len(matice[0])):
        radek:list = []
        for j in range(0,len(matice)):
            radek.append(matice[j][i])
        nmatice.append(radek)

    return nmatice


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
