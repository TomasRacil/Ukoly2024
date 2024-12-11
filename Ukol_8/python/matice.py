from __future__ import annotations
from typing import Union, List
import random

class Matice:
    def __init__(self, n: int, m: int, data=None):
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

    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        """Vynásobí aktuální matici maticí nebo skalárem."""
   
