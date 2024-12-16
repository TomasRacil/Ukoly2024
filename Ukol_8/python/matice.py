from __future__ import annotations
from typing import Union
import random


class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """Inicializuje matici n x m."""
        self.n = n
        self.m = m
        if data is None:
            self.data = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]
        else:
            self.data = data

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        return '\n'.join([' '.join(map(str, row)) for row in self.data])

    def __eq__(self, other: Matice) -> bool:
        """Porovná dvě matice na základě jejich dat."""
        if self.n != other.n or self.m != other.m:
            return False
        return self.data == other.data

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matice musí mít stejné rozměry pro sčítání.")
        result_data = [[self.data[i][j] + other.data[i][j] for j in range(self.m)] for i in range(self.n)]
        return Matice(self.n, self.m, result_data)

    def __mul__(self, other: Union[Matice, int]) -> Matice:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        if isinstance(other, Matice):
            if self.m != other.n:
                raise ValueError("Počet sloupců první matice musí být roven počtu řádků druhé matice.")
            result_data = [[sum(self.data[i][k] * other.data[k][j] for k in range(self.m)) for j in range(other.m)] for i in range(self.n)]
            return Matice(self.n, other.m, result_data)
        elif isinstance(other, int):
            result_data = [[self.data[i][j] * other for j in range(self.m)] for i in range(self.n)]
            return Matice(self.n, self.m, result_data)
        else:
            raise ValueError("Násobení je možné pouze s maticí nebo celým číslem.")

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        result_data = [[self.data[j][i] for j in range(self.n)] for i in range(self.m)]
        return Matice(self.m, self.n, result_data)


if __name__ == "__main__":
    # Vytvořte instance třídy Matice a otestujte metody
    matice1 = Matice(3, 2)
    matice2 = Matice(2, 4)

    print("Matice 1:")
    print(matice1)
    print("Matice 2:")
    print(matice2)

    soucet = matice1 + matice1  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    print(soucet)

    nasobek = matice1 * matice2  # Násobujeme matice1 a matice2
    print("Násobení matic:")
    print(nasobek)

    skalarni_nasobek = matice1 * 10
    print("Skálární násobek:")
    print(skalarni_nasobek)

    transponovana = matice1.transpozice()
    print("Transponovaná matice:")
    print(transponovana)
