from __future__ import annotations
from typing import Union
import random


class Matice:
    def __init__(self, n: int, m: int, data: list[list[int]] = None):
        """Inicializuje matici n x m."""
        self.n = n
        self.m = m
        
        if data:
            if len(data) == n and all((len(row) == m for row in data)):
                self.data = data
            else:
                raise ValueError("Velikost poskytnutých dat neodpovídá rozměrům matice.")
        else:
            matice = []
            for i in range(n):
                novy_radek = []
                for j in range(m):
                    novy_radek.append(random.randint(0,9))
                matice.append(novy_radek)
                
            self.data = matice


    def __str__(self) -> str:
        radky_jako_retezce = []
        for radek in self.data:
            radek_retezec = " ".join(map(str, radek))
            radky_jako_retezce.append(radek_retezec)
        stringova_reprezentace = "\n".join(radky_jako_retezce)

        return stringova_reprezentace

    def __add__(self, other: "Matice") -> "Matice":
        """Sečte aktuální matici s maticí other."""
        # Implementace součtu matic
        if self.n != other.n or self.m != other.m:
            raise ValueError("Matice musí mít stejné rozměry pro sčítání.")
    
        vysledek = []
        for i in range(len(self.data)):
            novy_radek = []
            for j in range(len(self.data[0])):
                soucet = self.data[i][j] + other.data[i][j]
                novy_radek.append(soucet)
            vysledek.append(novy_radek)

        return Matice(self.n, self.m, vysledek)
      
    def __mul__(self, other: Union[Matice, int]) -> Union[Matice, int]:
        """Vynásobí aktuální matici maticí nebo skalárem."""
        # Implementace násobení matic
        if isinstance(other, Matice):
            if self.m != other.n:
                raise ValueError("Pro maticové násobení musí počet sloupců první matice odpovídat počtu řádků druhé matice.")
            
            nasobeni = []
            for i in range(self.n):
                novy_radek = []
                for j in range(other.m):
                    soucin = 0
                    for k in range(other.n):
                        soucin += self.data[i][k] * other.data[k][j]
                    novy_radek.append(soucin)
                nasobeni.append(novy_radek)
            return Matice(self.n, other.m, nasobeni)
        
        elif isinstance(other, int):
            skalarem = []
            cislo = other
            for i in range(self.n):
                novy_radek = []
                for j in range(self.m):
                    novy_radek.append(self.data[i][j] * cislo)
                skalarem.append(novy_radek)
            return Matice(self.n, self.m, skalarem)
        
        else:
           raise TypeError("Lze násobit pouze jinou maticí nebo skalárem (int).") 

    def transpozice(self) -> Matice:
        """Vrátí transponovanou matici."""
        # Implementace transpozice matice
        transponovana = []
        for i in range(self.m):
            novy_radek = []
            for j in range(self.n):
                novy_radek.append(self.data[j][i])
            transponovana.append(novy_radek)
        
        return Matice(self.m, self.n, transponovana)
    
    def __eq__(self, other: Matice) -> bool:
        """Porovná aktuální matici s jinou maticí."""
        if not isinstance(other, Matice):
            return False
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
