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
    if len(matice1) == len(matice2) and len(matice1[0]) == len(matice2[0] and len(matice) > 0):
        return [[matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))] for i in range(len(matice1))]
    return None


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    """Vynásobí dvě matice, pokud je násobení proveditelné."""
    #A(nm) B(uv) are matrixes with dimensions n*m and u*v
    #m = u
    if len(matice1[0]) != len(matice2):
        return None

    #result of AB = R(nv)
    R = [[0 for elements in range(len(matice2[0]))] for row in range(len(matice1))]

    #R(ij) = A(i0)B(0j) + A(i1)B(1j) + ... + A(im)B(uj), m=u
    for i in range(len(R)):
        for j in range(len(R[0])):

            for k in range(len(matice2)):
                R[i][j] += matice1[i][k] * matice2[k][j]
    
    return R
            



def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    """Provede transpozici matice."""
    if len(matice) > 0:
        return [[matice[j][i] for j in range(len(matice[0]))] for i in range(len(matice))]
    return []


if __name__ == "__main__":
    matice1 = [[1, 2], [3, 4]]
    matice2 = [[5, 6], [7, 8]]
    expected_product = [[19, 22], [43, 50]]
    #self.assertEqual(nasobeni_matic(matice1, matice2), expected_product)

    matice3 = [[1, 2], [3, 4], [5, 6]]
    #self.assertIsNone(nasobeni_matic(matice1, matice3))
    #self.assertIsNone(nasobeni_matic(matice3, matice1))

    #self.assertEqual(nasobeni_matic([], []), [])
    #self.assertIsNone(nasobeni_matic(matice1, []))
    #self.assertIsNone(nasobeni_matic([], matice1))
