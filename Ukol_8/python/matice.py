from __future__ import annotations
from typing import Union
import random

MIN_VALUE = 0
MAX_VALUE = 9

class Matice:
    def __init__(self, n: int, m: int, data=None):
        """Inicializuje matici n x m."""
        self.n = n
        self.m = m
        if data is None:
            self.data = [[random.randint(MIN_VALUE, MAX_VALUE) for a in range(m)] for a in range(n)]
        else:
            self.data = data

    def __eq__(self, other: Matice) -> bool:
        return self.n == other.n and self.m == other.m and self.data == other.data

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        if not self.data: return ""
        else: return '\n'.join(' '.join(map(str, row)) for row in self.data)

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        # Implementace součtu matic
        if not self.data and not other: return []
        matice: list[list[int]] = []
        if len(self.data) != len(other.data) or any(len(row1) != len(row2) for row1, row2 in zip(self.data, other.data)):
            raise ValueError
    
        matice = []
        for r in range(len(self.data)):
            row = []
            for c in range(len(self.data[0])):
                row.append(self.data[r][c] + other.data[r][c])
            matice.append(row)
        
        return Matice(self.n, self.m, matice)

    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        # Implementace násobení matic
        if isinstance(other, int):
            return Matice(self.n, self.m, [[other*num for num in row] for row in self.data])
        if not self.data and not other.data:
            return []
        if not self.data and not other.data:
            raise ValueError
        if len(self.data[0]) != len(other.data):
            raise ValueError
        matice = []

        for r in range(len(self.data)):
            row = []
            for c in range(len(other.data[0])):
                row.append(sum(self.data[r][d] * other.data[d][c] for d in range(len(other.data))))
            matice.append(row)
        return Matice(self.n, self.m, matice)

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        # Implementace transpozice matice
        if not self.data: return []
        if not self.data[0]: return [[]]

        matice = []
        for c in range(self.m):
            row = []
            for r in range(self.n): 
                row.append(self.data[r][c])
            matice.append(row)
        
        return Matice(self.m, self.n, matice)

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
