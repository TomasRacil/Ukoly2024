from __future__ import annotations
from typing import Union
from random import randrange


class Matice:
    def __init__(self, n: int, m: int, data=None):
        self.n = n
        self.m = m

        if data != None:
            #fill matrix with data

            if self.n == len(data):
                if self.n != 0 and self.m != len(data[0]):
                    #matrix has some rows but they don't have the correct number of elements
                    raise ValueError
                elif self.n == 0 and self.m != 0:
                    #matrix has 0 rows but non-zero columns, which is not possible in this implementation
                    raise ValueError
                else:
                    self.data = data
                    return
            else:
                #n doesn't match data rows
                raise ValueError
        if n < 0 or m < 0:
            #matrix must have positive integer dimensions (0 is tolerated even though it's incorrect because of the tests)
            raise ValueError
        #fill matrix with random values
        self.data = [[ randrange(0,9) for _ in range(m)] for _ in range(n)]


    def __str__(self) -> str:
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
        #delete last newline character
        str_matrix = str_matrix[:-1]
        return str_matrix

    def __add__(self, other: Matice) -> Matice:
        if self.n == other.n:
            if self.n == 0:
                return Matice(0,0,[])
        if self.m == other.m:
            new_data = [[self.data[i][j] + other.data[i][j] for j in range(self.m)] for i in range(self.n)]
            return Matice(self.n,self.m, new_data)
        #dimensions don't match
        raise ValueError

    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        #zkusi nasobit matici matici
        try:
            #A(nm) B(uv) are matrixes with dimensions n*m and u*v
            if self.n != 0:
                #check if m = u
                if self.m != other.n:
                    #cannot multiply
                    raise ValueError
            elif other.n == 0:
                #both matrixes are empty
                return []
            else:
                #only one of the matrixes is empty
                raise ValueError

            #result of AB = R(nv)
            #init result matrix R with zeroes
            new_data = [[0 for _ in range(other.m)] for _ in range(self.n)]

            #R(ij) = A(i0)B(0j) + A(i1)B(1j) + ... + A(im)B(uj)
            for i in range(self.n):
                for j in range(other.m):
                    for k in range(other.n):
                        new_data[i][j] += self.data[i][k] * other.data[k][j]
            
            return Matice(self.n, other.m,new_data)
        except AttributeError:
            #other must be integer since matrix mult failed
            new_data = []
            for row in self.data:
                new_row = []
                for element in row:
                    new_row.append(element * other)
                new_data.append(new_row)
            return Matice(self.n,self.m,new_data)

    def transpozice(self) -> Matice:
        if len(self.data) > 0 and len(self.data[0]) > 0:
            return Matice(self.m,self.n,[[self.data[j][i] for j in range(len(self.data))] for i in range(len(self.data[0]))])
        elif len(self.data) > 0 and len(self.data[0]) == 0:
            #n rows, 0 columns
            return Matice(len(self.data),0,[[] for i in range(len(self.data))])
        #0 rows
        return Matice(0,0,[])
    
    #must be defined, otherwise tests cannot compare matrixes correctly (since they're objects)
    def __eq__(self, other):
        #matrixes are equal if their dimensions and data are the same
        return self.n == other.n and self.m == other.m and self.data == other.data


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
