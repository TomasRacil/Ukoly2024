from __future__ import annotations
from typing import Union
import random


class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """
        Inicializuje matici rozměrů n x m.
        Pokud není argument data zadán, matice se naplní náhodnými čísly v rozsahu 0..9.

        Args:
            n (int): Počet řádků
            m (int): Počet sloupců
            data (list[list[int]], optional): Seznam seznamů s předem danými hodnotami matice
        """
        self.n = n
        self.m = m

        if data is not None:
            self.data = data
        else:
            self.data = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]

    def __eq__(self, other: Matice) -> bool:
        """
        Porovnání dvou matic pro účely `==`.
        Dvě matice jsou rovné, pokud mají stejné rozměry a identická data.
        """
        if not isinstance(other, Matice):
            return NotImplemented
        return self.n == other.n and self.m == other.m and self.data == other.data

    def __str__(self) -> str:
        """
        Vrátí stringovou reprezentaci matice (řádky oddělené novým řádkem, prvky oddělené mezerou).
        """
        radky = []
        for row in self.data:
            radky.append(" ".join(str(x) for x in row))
        return "\n".join(radky)

    def __add__(self, other: Matice) -> Matice:
        """
        Přetížený operátor + pro sčítání dvou matic.
        Ověří, že obě matice mají shodné rozměry (n x m).
        V případě nesouladu rozměrů vyvolá výjimku ValueError.
        """
        if self.n != other.n or self.m != other.m:
            raise ValueError("Součet nelze provést - matice nemají stejné rozměry.")

        vysledek_data = []
        for i in range(self.n):
            radek = []
            for j in range(self.m):
                radek.append(self.data[i][j] + other.data[i][j])
            vysledek_data.append(radek)

        return Matice(self.n, self.m, vysledek_data)

    def __mul__(self, other: Union[Matice, int]) -> Matice:
        """
        Přetížený operátor * pro násobení matic nebo násobení matice skalárem.

        Args:
            other (Matice | int): Další matice k vynásobení nebo skalár (int).

        Raises:
            ValueError: Pokud se jedná o násobení matic, ale rozměry nesedí.
            TypeError: Pokud other není Matice ani int.

        Returns:
            Matice: Výsledek násobení (matice).
        """
        # 1) Násobení matic
        if isinstance(other, Matice):
            if self.m != other.n:
                raise ValueError("Násobení matic nelze provést - rozměry nesedí (self.m != other.n).")

            n, m, p = self.n, self.m, other.m
            vysledek_data = []
            for i in range(n):
                radek = []
                for j in range(p):
                    suma = 0
                    for k in range(m):
                        suma += self.data[i][k] * other.data[k][j]
                    radek.append(suma)
                vysledek_data.append(radek)
            return Matice(n, p, vysledek_data)

        # 2) Násobení skalárem (int)
        elif isinstance(other, int):
            vysledek_data = []
            for i in range(self.n):
                radek = []
                for j in range(self.m):
                    radek.append(self.data[i][j] * other)
                vysledek_data.append(radek)
            return Matice(self.n, self.m, vysledek_data)

        else:
            raise TypeError("Nepodporovaný typ pro násobení: musí být Matice nebo int.")

    def transpozice(self) -> Matice:
        """
        Vrátí transponovanou matici (o rozměru [m x n]).
        """
        transponovana_data = []
        for col_index in range(self.m):
            radek = []
            for row_index in range(self.n):
                radek.append(self.data[row_index][col_index])
            transponovana_data.append(radek)
        return Matice(self.m, self.n, transponovana_data)


if __name__ == "__main__":
    # Jednoduchá ukázka
    mat1 = Matice(2, 2, [[1, 2], [3, 4]])
    mat2 = Matice(2, 2, [[5, 6], [7, 8]])
    print("mat1:")
    print(mat1)
    print("mat2:")
    print(mat2)

    print("Součet (mat1 + mat2):")
    print(mat1 + mat2)

    print("Násobení (mat1 * mat2):")
    print(mat1 * mat2)

    print("Transpozice (mat1):")
    print(mat1.transpozice())
