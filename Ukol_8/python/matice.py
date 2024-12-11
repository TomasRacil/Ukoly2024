from __future__ import annotations
from typing import Union
import random

class Matice:
    def __init__(self, n: int, m: int, data=None):
        """Inicializuje matici n x m."""
        self.n = n
        self.m = m
        if data is None:
            self.data = []
            for _ in range(n):
                row = []
                for _ in range(m):
                    row.append(random.randint(0, 3))  
                self.data.append(row)
        else:
            self.data = data

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        output = []
        for row in self.data:
            output.append(' '.join(map(str, row)))
        return '\n'.join(output)

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        if self.n != other.n or self.m != other.m:
            raise ValueError("neplatné rozměry matic")
        new_data = []
        for i in range(self.n):
            new_row = []
            for j in range(self.m):
                new_row.append(self.data[i][j] + other.data[i][j])
            new_data.append(new_row)
        return Matice(self.n, self.m, new_data)

    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        if isinstance(other, Matice):
            if self.m != other.n:
                raise ValueError("neplatné rozměry")
            new_data = []
            for i in range(self.n):
                new_row = []
                for j in range(other.m):
                    suma = 0
                    for k in range(self.m):
                        suma += self.data[i][k] * other.data[k][j]
                    new_row.append(suma)
                new_data.append(new_row)
            return Matice(self.n, other.m, new_data)
        elif isinstance(other, int):
            new_data = []
            for i in range(self.n):
                new_row = [val * other for val in self.data[i]]
                new_data.append(new_row)
            return Matice(self.n, self.m, new_data)
        else:
            raise TypeError("neplatné násobení")

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        new_data = []
        for i in range(self.m):
            new_row = []
            for j in range(self.n):
                new_row.append(self.data[j][i])
            new_data.append(new_row)
        return Matice(self.m, self.n, new_data)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Matice):
            return False
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
