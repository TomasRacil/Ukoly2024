from random import randrange


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    #Matrix A = (aij) of type n*m, where i = 1,2,3,...,n and j = 1,2,3,...,m has n rows and m columns 
    if n < 0 or m < 0:
        return None
    
    matice: list[list[int]] = [[ randrange(0,9) for element in range(m)] for row in range(n)]
    return matice

def reprezentace_matice(matice: list[list[int]]) -> str:
    str_matrix : str = ""
    if matice != None:
        for i in range(len(matice)):
            #for each row
            for j in range(len(matice[i])):
                #for each element
                str_matrix += str(matice[i][j])
                if j < len(matice[i]) - 1:
                    str_matrix += str(" ")
            str_matrix += "\n"
    return str_matrix


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    #matrixes must have the same dimensions
    if len(matice1) == len(matice2):
        if len(matice1) == 0:
            #both matrixes are empty
            return []
        if len(matice1[0]) == len(matice2[0]):
            return [[matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))] for i in range(len(matice1))]
    return None


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    #A(nm) B(uv) are matrixes with dimensions n*m and u*v

    if len(matice1) != 0:
        #check if m = u
        if len(matice1[0]) != len(matice2):
            #cannot multiply
            return None
    elif len(matice2) == 0:
        #both matrixes are empty
        return []
    else:
        #only one of the matrixes is empty
        return None

    #result of AB = R(nv)
    #init result matrix R with zeroes
    R = [[0 for _ in range(len(matice2[0]))] for _ in range(len(matice1))]

    #R(ij) = A(i0)B(0j) + A(i1)B(1j) + ... + A(im)B(uj)
    for i in range(len(R)):
        for j in range(len(R[0])):
            for k in range(len(matice2)):
                R[i][j] += matice1[i][k] * matice2[k][j]
    
    return R
            



def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    if len(matice) > 0 and len(matice[0]) > 0:
        return [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]
    elif len(matice) > 0 and len(matice[0]) == 0:
        #n rows, 0 columns
        return [[] for i in range(len(matice))]
    #0 rows
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