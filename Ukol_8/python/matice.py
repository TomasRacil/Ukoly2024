from __future__ import annotations
from typing import Union, List
import random

class Matice:
    def __init__(self, n: int, m: int, data=None):
        #inicializuje matici n x m
        self.n = n  #počet řádků
        self.m = m  #počet sloupců
        if data is None:
            #když data nejsou poskytnuta, generujeme random čísla od 0 do 9
            self.data = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]
        else:
            #když jsou poskytnuta, použijeme je
            if len(data) != n or any(len(row) != m for row in data):
                raise ValueError("Rozměry dat neodpovídají rozměrům matice")
            self.data = data

    def __str__(self) -> str:
        #vrací matici ve stringu
        return '\n'.join([' '.join(map(str, row)) for row in self.data])

    def __add__(self, other: Matice) -> Matice:
        #sečte aktuální matici s maticí other
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matice musí mít stejné rozměry")
        #součet prvků v matici
        result_data = [
            [self.data[i][j] + other.data[i][j] for j in range(self.m)]
            for i in range(self.n)
        ]
        return Matice(self.n, self.m, result_data)

    def __mul__(self, other: Union[Matice, int]) -> Matice:
        # ynásobí aktuální matici maticí nebo skalárem
        if isinstance(other, Matice):
            #násobení matic 
            if self.m != other.n:
                raise ValueError("Počet sloupců první matice se musí rovnat počtu řádků druhé matice")
            
            result_data = [
                [sum(self.data[i][k] * other.data[k][j] for k in range(self.m)) for j in range(other.m)]
                for i in range(self.n)
            ]
            return Matice(self.n, other.m, result_data)

        elif isinstance(other, int):
            #násobení skalárem
            result_data = [
                [self.data[i][j] * other for j in range(self.m)]
                for i in range(self.n)
            ]
            return Matice(self.n, self.m, result_data)
        
        else:
            raise TypeError("Matici lze násobit pouze maticí nebo celým číslem")

    def transpozice(self) -> Matice:
        #vrátí transponovanou matici.
        result_data = [
            [self.data[j][i] for j in range(self.n)]
            for i in range(self.m)
        ]
        return Matice(self.m, self.n, result_data)


if __name__ == "__main__":
    matice1 = Matice(3, 2)  #matice 3x2
    matice2 = Matice(2, 4)  #matice 2x4

    print("Matice 1:")
    print(matice1)
    print("Matice 2:")
    print(matice2)

    #sčítání matic
    try:
        soucet = matice1 + matice1  #sečte matici samu se sebou
        print("Součet matic:")
        print(soucet)
    except ValueError as e:
        print(f"Chyba při sčítání: {e}")

    #násobení matic
    try:
        nasobek = matice1 * matice2  #násobení matice1 s matice2
        print("Násobení matic:")
        print(nasobek)
    except ValueError as e:
        print(f"Chyba při násobení: {e}")

    #skálární násobení
    skalarni_nasobek = matice1 * 10
    print("Skálární násobek:")
    print(skalarni_nasobek)

    #transponovaná matice
    transponovana = matice1.transpozice()
    print("Transponovaná matice:")
    print(transponovana)
