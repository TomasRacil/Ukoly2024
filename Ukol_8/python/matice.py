#reupload
from __future__ import annotations
from typing import Union
import random

class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """Inicializuje matici n x m."""
        self.n = n
        self.m = m
        self.data = data if data else [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        return "\n".join(" ".join(map(str, radek)) for radek in self.data)

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matice musí mít stejné rozměry pro sčítání.")
        result_data = [
            [self.data[i][j] + other.data[i][j] for j in range(self.m)]
            for i in range(self.n)
        ]
        return Matice(self.n, self.m, result_data)

    def __mul__(self, other: Union[Matice, int]) -> Matice:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        if isinstance(other, Matice):
            if self.m != other.n:
                raise ValueError("Počet sloupců první matice musí být roven počtu řádků druhé matice.")
            result_data = [
                [
                    sum(self.data[i][k] * other.data[k][j] for k in range(self.m))
                    for j in range(other.m)
                ]
                for i in range(self.n)
            ]
            return Matice(self.n, other.m, result_data)
        elif isinstance(other, int):
            result_data = [
                [self.data[i][j] * other for j in range(self.m)]
                for i in range(self.n)
            ]
            return Matice(self.n, self.m, result_data)
        else:
            raise TypeError("Násobení je možné pouze s jinou maticí nebo celým číslem.")

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        result_data = [[self.data[j][i] for j in range(self.n)] for i in range(self.m)]
        return Matice(self.m, self.n, result_data)

    def __eq__(self, other: Matice) -> bool:
        """Porovná dvě matice."""
        if not isinstance(other, Matice):
            return False
        return self.n == other.n and self.m == other.m and self.data == other.data


if __name__ == "__main__":
    matice1 = Matice(3, 2)
    matice2 = Matice(2, 4)

    print("Matice 1:")
    print(matice1)

    print("\nMatice 2:")
    print(matice2)

    soucet = matice1 + matice1
    print("\nSoučet matic:")
    print(soucet)

    nasobek = matice1 * matice2
    print("\nNásobení matic:")
    print(nasobek)

    skalarni_nasobek = matice1 * 10
    print("\nSkálární násobek:")
    print(skalarni_nasobek)

    transponovana = matice1.transpozice()
    print("\nTransponovaná matice:")
    print(transponovana)
