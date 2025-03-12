from __future__ import annotations
from typing import Union, List
import random


class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """Inicializuje matici n x m."""
        self.n = n  # Počet řádků
        self.m = m  # Počet sloupců
        if data is None:
            # Pokud data nejsou poskytnuta, generujeme náhodná čísla mezi 0 a 9
            self.data = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]
        else:
            # Pokud jsou data poskytnuta, použijeme je
            self.data = data

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        return '\n'.join([' '.join(map(str, row)) for row in self.data])

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matice musí mít stejné rozměry pro sčítání.")
        # Provede součet matic po prvcích
        result_data = [
            [self.data[i][j] + other.data[i][j] for j in range(self.m)]
            for i in range(self.n)
        ]
        return Matice(self.n, self.m, result_data)

    def __mul__(self, other: Union[Matice, int]) -> Matice:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        if isinstance(other, Matice):
            # Násobení matic (pro maticové násobení musí být počet sloupců první matice
            # roven počtu řádků druhé matice)
            if self.m != other.n:
                raise ValueError("Počet sloupců první matice musí být rovný počtu řádků druhé matice.")
            
            result_data = [
                [sum(self.data[i][k] * other.data[k][j] for k in range(self.m)) for j in range(other.m)]
                for i in range(self.n)
            ]
            return Matice(self.n, other.m, result_data)

        elif isinstance(other, int):
            # Násobení skalárem
            result_data = [
                [self.data[i][j] * other for j in range(self.m)]
                for i in range(self.n)
            ]
            return Matice(self.n, self.m, result_data)
        
        else:
            raise TypeError("Matici lze násobit pouze maticí nebo celým číslem.")

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        result_data = [
            [self.data[j][i] for j in range(self.n)]
            for i in range(self.m)
        ]
        return Matice(self.m, self.n, result_data)

    def __eq__(self, other: Matice) -> bool:
        """Porovná matici s jinou maticí."""
        if not isinstance(other, Matice):
            return False
        return self.data == other.data


if __name__ == "__main__":
    # Vytvoření instancí matic
    matice1 = Matice(3, 2)  # Matice 3x2
    matice2 = Matice(2, 4)  # Matice 2x4

    print("Matice 1:")
    print(matice1)
    print("Matice 2:")
    print(matice2)

    # Sčítání matic
    try:
        soucet = matice1 + matice1  # Sečteme matici1 samu se sebou
        print("Součet matic:")
        print(soucet)
    except ValueError as e:
        print(f"Chyba při sčítání: {e}")

    # Násobení matic
    try:
        nasobek = matice1 * matice2  # Násobíme matice1 a matice2
        print("Násobení matic:")
        print(nasobek)
    except ValueError as e:
        print(f"Chyba při násobení: {e}")

    # Skálární násobení
    skalarni_nasobek = matice1 * 10
    print("Skálární násobek:")
    print(skalarni_nasobek)

    # Transpozice matice
    transponovana = matice1.transpozice()
    print("Transponovaná matice:")
    print(transponovana)
