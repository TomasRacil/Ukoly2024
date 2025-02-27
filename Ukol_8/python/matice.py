from __future__ import annotations
from typing import Union
import random


class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """Inicializuje matici n x m."""
        matice:list[list[int]] = []
        for i in range(0,n):
            radek:list[int] = []
            for j in range(0,m):
                radek.append(random.randint(0,9))
            matice.append(radek)
        self.data = matice
        self.n = n
        self.m = m
        pass

    def __str__(self) -> str:
        """Vrátí stringovou reprezentaci matice."""
        s:str  = ""
        for radek in self.data:
            for cislo in radek:
                s += str(cislo) + " "
            s+= "\n"
        return s

    def __add__(self, other: Matice) -> Matice:
        """Sečte aktuální matici s maticí other."""
        # Implementace součtu matic
        matice: list[list[int]] = []
        if len(self.data) == len(other.data) and len(self.data[0]) == len(other.data[0]):
            for i in range (0,len(self.data)):
                radek:list[int] = []
                for j in range(0,len(self.data[0])):
                    soucet = self.data[i][j] + other.data[i][j]
                    radek.append(soucet)
                matice.append(radek)
            soucet = Matice(self.n,self.m,)
            soucet.data = matice
            return soucet
        else:
            print("tyto matice nejde scitat")
            return None

    def __mul__(self, other: Union[Matice, int]) -> Matice:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        matice: list[list[int]] = []
        if type(other) == Matice:
            if self.m == other.n:
                for i in range(0,self.n):
                    radek:list = []
                    for j in range(0,other.m):
                        soucin = 0
                        for k in range (0,other.n):
                            soucin += self.data[i][k] * other.data[k][j]
                        radek.append(soucin)
                    matice.append(radek)
                souc = Matice(self.n,other.m)
                souc.data = matice
                return souc
            else:
                print("tyto matice nejde nasobit")
                return None
        elif type(other) == int:
            ndata:list[list[int]] = []
            for radek in self.data:
                nradek:list = []
                for cislo in radek:
                    ncislo:int
                    ncislo = cislo*other
                    nradek.append(ncislo)
                ndata.append(nradek)
            soucin = Matice(self.n,self.m)
            soucin.data = ndata
            return soucin
    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        nmatice: list[list[int]] = []
        for i in range(0,self.m):
            radek:list = []
            for j in range(0,self.n):
                radek.append(self.data[j][i])
            nmatice.append(radek)
        trans = Matice(self.m,self.n)
        trans.data = nmatice
        return trans


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
