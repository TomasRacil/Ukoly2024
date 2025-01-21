from __future__ import annotations
from typing import Union
import random


class Matice:
    def __init__(self, n: int, m: int, data=None):
        """Inicializuje matici n x m."""
        self.n = n
        self.m = m
        if data is None:
            # Inicializace náhodných hodnot od 0 do 9
            self.data = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]
        else:
            self.data = data

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        return '\n'.join([' '.join(map(str, row)) for row in self.data])

    def __eq__(self, other: Matice) -> bool:
        if not isinstance(other, Matice):
            return NotImplemented
        return self.n == other.n and self.m == other.m and self.data == other.data

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matici musí mít stejné rozměry pro sčítání.")

        result_data = [[self.data[i][j] + other.data[i][j] for j in range(self.m)] for i in range(self.n)]
        return Matice(self.n, self.m, result_data)

    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        if isinstance(other, int):
            # Skálární násobení
            result_data = [[self.data[i][j] * other for j in range(self.m)] for i in range(self.n)]
            return Matice(self.n, self.m, result_data)

        elif isinstance(other, Matice):
            # Násobení matic
            if self.m != other.n:
                raise ValueError("Počet sloupců první matice musí být shodný s počtem řádků druhé matice.")

            result_data = [[sum(self.data[i][k] * other.data[k][j] for k in range(self.m)) for j in range(other.m)] for
                           i in range(self.n)]
            return Matice(self.n, other.m, result_data)

        else:
            raise ValueError("Může být násobeno pouze s jinou maticí nebo skalárem.")

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        transposed_data = [[self.data[j][i] for j in range(self.n)] for i in range(self.m)]
        return Matice(self.m, self.n, transposed_data)

if __name__ == "__main__":
    # Vytvořte instance třídy Matice a otestujte metody
    matice1 = Matice(3, 2)
    matice2 = Matice(2, 4)

    print("Matice 1:")
    print(matice1)
    print("Matice 2:")
    print(matice2)

    # Před úpravou součtu zajistíme, že matice1 a matice1 mají stejné rozměry
    matice3 = Matice(3, 2)  # Tvoříme novou matici se stejnými rozměry jako matice1
    soucet = matice1 + matice3  # Sečteme matici1 a matici3
    print("Součet matic:")
    print(soucet)

    # Změna rozměrů matice2 pro správné násobení
    matice2 = Matice(2, 3, data=[[1, 2, 3], [4, 5, 6]])  # Specifické hodnoty pro testování
    print("Matice 2 (nová):")
    print(matice2)

    nasobek = matice1 * matice2  # Násobíme matice1 a matice2
    print("Násobení matic:")
    print(nasobek)

    skalarni_nasobek = matice1 * 10
    print("Skálární násobek:")
    print(skalarni_nasobek)

    transponovana = matice1.transpozice()
    print("Transponovaná matice:")
    print(transponovana)
