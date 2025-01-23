from __future__ import annotations
from typing import Union
import random


class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """Inicializuje matici n x m."""
        if data is None:
            self.data = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]
        else:
            self.data = data
        self.m = m
        self.n = n

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        return '\n'.join([' '.join(map(str, radek)) for radek in self.data])

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        if self.m != other.m or  self.n != other.n:
            raise ValueError("Matice musí mít stejné rozměry")
        return Matice(self.n, self.m, [[self.data[i][j] + other.data[i][j] for j in range(self.m)] for i in range(self.n)])


    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        if isinstance(other, Matice):
            if len(self.data[0]) != len(other.data):
                raise ValueError("Počet sloupců první matice musí být roven počtu řádků druhé matice")
            return Matice(len(self.data), len(other.data[0]), [[sum(self.data[i][k] * other.data[k][j] for k in range(len(other.data))) for j in range(len(other.data[0]))] for i in range(len(self.data))])
        elif isinstance(other, int):
            return Matice(len(self.data), len(self.data[0]), [[self.data[i][j] * other for j in range(len(self.data[0]))] for i in range(len(self.data))])
        else:
            raise ValueError("Není možné násobit matici s tímto typem")

    def __eq__(self, other):
        """Porovná matici s jinou maticí."""
        return self.data == other.data

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        return Matice(self.m, self.n, [[self.data[j][i] for j in range(self.n)] for i in range(self.m)])


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
