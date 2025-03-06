from __future__ import annotations
from typing import Union
import random

class matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None) -> None:
        self.n: int = n
        self.m: int = m
        if data is not None:
            self.data: list[list[int]] = data
        else:
            if n <= 0:
                self.data = []
            else:
                self.data = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]

    def __str__(self) -> str:
        if not self.data:
            return ""
        return "\n".join(" ".join(str(x) for x in row) for row in self.data)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, matice):
            return False
        return self.n == other.n and self.m == other.m and self.data == other.data

    def __add__(self, other: matice) -> matice:
        if self.n != other.n or self.m != other.m:
            raise ValueError("matice nemaji stejne rozmery")
        new_data: list[list[int]] = []
        for i in range(self.n):
            new_row: list[int] = []
            for j in range(self.m):
                new_row.append(self.data[i][j] + other.data[i][j])
            new_data.append(new_row)
        return matice(self.n, self.m, new_data)

    def __mul__(self, other: Union[matice, int]) -> matice:
        if isinstance(other, int):
            new_data: list[list[int]] = [[x * other for x in row] for row in self.data]
            return matice(self.n, self.m, new_data)
        elif isinstance(other, matice):
            if self.m != other.n:
                raise ValueError("pocet sloupcu prvni matice se nerovna poctu radku druhe")
            new_data: list[list[int]] = []
            for i in range(self.n):
                new_row: list[int] = []
                for j in range(other.m):
                    sum_val: int = 0
                    for k in range(self.m):
                        sum_val += self.data[i][k] * other.data[k][j]
                    new_row.append(sum_val)
                new_data.append(new_row)
            return matice(self.n, other.m, new_data)
        else:
            raise ValueError("nasobeni pouze matici nebo skalarem")

    def transpozice(self) -> matice:
        if not self.data:
            return matice(0, 0, [])
        new_data: list[list[int]] = [list(row) for row in zip(*self.data)]
        return matice(self.m, self.n, new_data)


if __name__ == "__main__":
    matice1 = matice(3, 2)
    matice2 = matice(2, 4)

    print("matice 1")
    print(matice1)
    print("matice 2")
    print(matice2)

    soucet = matice1 + matice1
    print("soucet matic")
    print(soucet)

    try:
        nasobek = matice1 * matice2
        print("nasobeni matic")
        print(nasobek)
    except ValueError as e:
        print(e)

    skalarni_nasobek = matice1 * 10
    print("skalarni nasobek")
    print(skalarni_nasobek)

    transponovana = matice1.transpozice()
    print("transponovana matice")
    print(transponovana)
