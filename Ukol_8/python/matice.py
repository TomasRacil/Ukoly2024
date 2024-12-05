from __future__ import annotations
from typing import Union
from random import randrange


class Matice:
    def __init__(self, n: int, m: int, data=None):
        """Inicializuje matici n x m."""
        #Matrix A = (aij) of type n*m, where i = 1,2,3,...,n and j = 1,2,3,...,m has n rows and m columns 
        if n < 0 or m < 0:
            return None
        self.data = [[ randrange(0,9) for element in range(m)] for row in range(n)]


    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        str_matrix : str = ""
        if self.data != None:
            for i in range(len(self.data)):
                #for each row
                for j in range(len(self.data[i])):
                    #for each element
                    str_matrix += str(self.data[i][j])
                    if j < len(self.data[i]) - 1:
                        str_matrix += str(" ")
                str_matrix += "\n"
        return str_matrix

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        # Implementace součtu matic
        if len(self.data) == len(other.data):
            if len(self.data) == 0:
                #both matrixes are empty
                return []
            if len(self.data[0]) == len(other.data[0]):
                return [[self.data[i][j] + other.data[i][j] for j in range(len(self.data[0]))] for i in range(len(self.data))]
        return None

    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        try:
            #A(nm) B(uv) are matrixes with dimensions n*m and u*v

            if len(self.data) != 0:
                #check if m = u
                if len(self.data[0]) != len(other.data):
                    #cannot multiply
                    return None
            elif len(other.data) == 0:
                #both matrixes are empty
                return []
            else:
                #only one of the matrixes is empty
                return None

            #result of AB = R(nv)
            #init result matrix R with zeroes
            R = [[0 for _ in range(len(other.data[0]))] for _ in range(len(self.data))]

            #R(ij) = A(i0)B(0j) + A(i1)B(1j) + ... + A(im)B(uj)
            for i in range(len(R)):
                for j in range(len(R[0])):
                    for k in range(len(other.data)):
                        R[i][j] += self.data[i][k] * other.data[k][j]
            
            return R
        except AttributeError:
            #other is int
            R = []
            for row in self.data:
                new_row = []
                for element in row:
                    new_row.append(element * other)
                R.append(new_row)
            return R

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        if len(self.data) > 0 and len(self.data[0]) > 0:
            return [[self.data[j][i] for j in range(len(self.data))] for i in range(len(self.data[0]))]
        elif len(self.data) > 0 and len(self.data[0]) == 0:
            #n rows, 0 columns
            return [[] for i in range(len(self.data))]
        #0 rows
        return []


if __name__ == "__main__":
    # Vytvořte instance třídy Matice a otestujte metody
    matice1 = Matice(3, 2)
    matice2 = Matice(2, 4)

    print("Matice 1:")
    print(matice1)
    print("Matice 2:")
    print(matice2)

    soucet = matice1+matice1  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    print(soucet)

    nasobek = matice1*matice2  # Násobujeme matice1 a matice2
    print("Násobení matic:")
    print(nasobek)

    skalarni_nasobek = matice1*10
    print("Skálární násobek:")
    print(skalarni_nasobek)

    transponovana = matice1.transpozice()
    print("Transponovaná matice:")
    print(transponovana)
