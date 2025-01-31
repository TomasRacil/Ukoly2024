
from __future__ import annotations
from typing import Union
import random


class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """Inicializuje matici n x m."""
        self.n = n
        self.m = m
        
        if data is None: # rand matice pokud není předáno parametrem
            self.data = [[random.randint(0, 9) for col in range(m)] for row in range(n)]
        else :
            self.data = data
     


    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        return '\n'.join(' '.join(map(str, row)) for row in self.data)


    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matrix size does not match! ")
        else:
            result = [[self.data[row][col] + other.data[row][col] for col in range(self.m)] for row in range(self.n)]
            return Matice(self.n, self.m, result)


    def __mul__(self, other: Union[Matice, int]) -> Matice:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        if type(other) is int:
            result = [[self.data[row][col] * other for col in range(self.m)] for row in range(self.n)]
            return Matice(self.n, self.m, result)
        elif type(other) is Matice:
            if self.m != other.n:
                raise ValueError("Nelze provést násobení matic.")
            else:
                result = [[sum(self.data[row][k] * other.data[k][col] for k in range(self.m)) for col in range(other.m)] for row in range(self.n)]
                return Matice(self.n, other.m, result)
        else:
            raise ValueError("Wrong matrix multiplier type! ")
        

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        result = [[self.data[col][row] for col in range(self.n)] for row in range(self.m)]
        return Matice(self.m, self.n, result)

    def __eq__(self, other):
        """Porovná dvě matice."""
        return self.data == other.data

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
