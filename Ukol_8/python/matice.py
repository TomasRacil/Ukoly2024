import random
from typing import Union, Optional, List


class Matice:
    def __init__(self, n: int, m: int, data: Optional[List[List[int]]] = None):
        self.n = n
        self.m = m
        if data:
            if len(data) != n or any(len(row) != m for row in data):
                raise ValueError("Rozměry dat neodpovídají rozměrům matice.")
            self.data = data
        else:
            self.data = [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]

    def __str__(self) -> str:
        return "\n".join(" ".join(map(str, row)) for row in self.data)

    def __add__(self, other: "Matice") -> "Matice":
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matice musí mít stejné rozměry pro sčítání.")
        new_data = [
            [self.data[i][j] + other.data[i][j] for j in range(self.m)]
            for i in range(self.n)
        ]
        return Matice(self.n, self.m, new_data)

    def __mul__(self, other: Union["Matice", int]) -> "Matice":
        if isinstance(other, Matice):
            if self.m != other.n:
                raise ValueError("Počet sloupců první matice se musí rovnat počtu řádků druhé matice.")
            new_data = [
                [
                    sum(self.data[i][k] * other.data[k][j] for k in range(self.m))
                    for j in range(other.m)
                ]
                for i in range(self.n)
            ]
            return Matice(self.n, other.m, new_data)
        elif isinstance(other, int):
            new_data = [
                [self.data[i][j] * other for j in range(self.m)]
                for i in range(self.n)
            ]
            return Matice(self.n, self.m, new_data)
        else:
            raise ValueError("Násobení je definováno pouze pro matici nebo celé číslo.")

    def transpozice(self) -> "Matice":
        new_data = [[self.data[j][i] for j in range(self.n)] for i in range(self.m)]
        return Matice(self.m, self.n, new_data)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Matice):
            return False
        return self.n == other.n and self.m == other.m and self.data == other.data
