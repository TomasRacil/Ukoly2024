from __future__ import annotations
from typing import Union
import random


class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """Inicializuje matici n x m."""
        self.n = n #pocet radku
        self.m = m #pocet sloupcu
        if data is None:
            self.data = []
            for i in range(n):
                row = []
                for j in range(m):
                    row.append(random.randint(0, 9))
                self.data.append(row)
            
        else:
            self.data = data
        

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        reprezentace = []
        for row in self.data:
            #pro kazdy prvek v aktualnim radku row pouzijeme funkci
            #pouzijeme funkci str(prvek), ktera prvek prevede na string
            #join pak spoji vsechny prevedene hodnoty do jednoho retezce
            #ve kterem mezi hodnotami bude mezera
            reprezentace.append(" ".join(str(prvek) for prvek in row))
        return "\n".join(reprezentace) #tento radek spoji vsechny radky do jednoho a vlozi do reperezentace


    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matice nemaji stejne rozmery pro soucet")
        
        result = [] #prazdny seznam ktery bude uchovavat radky vysledne matice
        for radek in range(self.n): #radek je index aktualniho radku
            row = [self.data[radek][j] + other.data[radek][j] for j in range(self.m)]
            result.append(row)
        return Matice(self.n, self.m, result)


    def __mul__(self, other: Union[Matice, int]) -> Matice:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        # Implementace násobení matic
        if isinstance(other, Matice): #pokud je other instanci tridy Matice:
            if self.m != other.n: #pokud pocet sloupcu prvni matice 
                #neni roven poctu radku druhe matice 
                #vyvolame vyjjimku
                raise ValueError("Pocet sloupcu prvni matice neni roven poctu radku druhe")
            
            result = []
            for i in range(self.n):
                row = []
                for j in range(other.m):
                    value = sum(self.data[i][k] * other.data[k][j] for k in range(self.m))
                    row.append(value)
                result.append(row)
            return Matice(self.n, other.m, result)
        
        elif isinstance(other, int): #pokud other neni matice ale skalar:
            result = []
            for i in range(self.n):
                row = [self.data[i][j] * other for j in range(self.m)]
                result.append(row)
            return Matice(self.n, self.m, result)
        
        else:
            raise ValueError("Muzete nasobit pouze matici nebo celym cislem")

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        transponovana = []
        for j in range(self.m):
            row = [self.data[i][j] for i in range(self.n)]
            transponovana.append(row)
        return Matice(self.m, self.n, transponovana)


    def __eq__(self, other: Matice) -> bool:
        """Porovná dvě matice, zda mají stejné rozměry a data."""
        return self.n == other.n and self.m == other.m and self.data == other.data


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
