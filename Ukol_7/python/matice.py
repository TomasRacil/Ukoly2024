from random import randrange


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    """Vytvoří matici n x m s náhodnými celými čísly od 0 do 9."""
    matice: list[list[int]] = [[ randrange(0,9) for element in range(m)] for row in range(n)]
    return matice
            


def reprezentace_matice(matice: list[list[int]]) -> str:
    """Vrátí stringovou reprezentaci matice."""
    str_matrix : str = ""
    for i in range(len(matice)):
        #for each list
        for j in range(len(matice[i])):
            #for each element
            str_matrix += str(matice[i][j])
            if j < len(matice[i]) - 1:
                str_matrix += str(" ")
        str_matrix += "\n"
    return str_matrix


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Sečte dvě matice, pokud mají stejné rozměry."""
    if len(matice1) == len(matice2) and len(matice1[0]) == len(matice2[0]) and len(matice1) > 0:
        return [[matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))] for i in range(len(matice1))]
    return None


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    #A(nm) B(uv) are matrixes with dimensions n*m and u*v
    #m = u
    if len(matice1[0]) != len(matice2):
        return None

    #result of AB = R(nv)
    R = [[0 for _ in range(len(matice2[0]))] for _ in range(len(matice1))]

    #R(ij) = A(i0)B(0j) + A(i1)B(1j) + ... + A(im)B(uj), m=u
    for i in range(len(R)):
        for j in range(len(R[0])):
            for k in range(len(matice2)):
                R[i][j] += matice1[i][k] * matice2[k][j]
    
    return R
            



def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice."""
    if len(matice) > 0:
        return [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]
    return []

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